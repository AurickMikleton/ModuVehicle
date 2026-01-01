#include "car.hpp"

using namespace godot;

void MoVeCar::_ready() {
    //pass
}

void MoVeCar::update() {
    float load = m_transmission->get_reflected_load(m_engine->get_current_rpm(), m_engine->get_throttle());
    m_engine->set_reflected_load(load);
}

void MoVeCar::update_wheels() {
    wheels.clear();
    wheels.reserve(m_wheel_paths.size());

    for (int i = 0; i < m_wheel_paths.size(); i++) {
        NodePath path = m_wheel_paths[i];
        if (!has_node(path)) {
            WARN_PRINT(vformat("Wheel path not found: %s", path));
            continue;
        }
        MoVeWheel *wheel = get_node<MoVeWheel>(path);
        if (wheel) wheels.push_back(wheel);
    }
}

void MoVeCar::update_suspension() {
    for (auto &wheel : wheels) {
        if (!wheel->is_colliding()) {
            wheel->set_normal_force(0.0f);
            continue;
        }

        Vector3 target = wheel->get_target_position();
        target.y = (-(wheel->m_resting_distnace + wheel->m_wheel_radius + 0.2));
        wheel->set_target_position(target);

        Vector3 contact = wheel->get_collision_point();
        Vector3 up_direction = wheel->get_global_transform().get_basis().get_column(1);
        float spring_length = wheel->get_global_position().distance_to(contact) - wheel->m_wheel_radius;

        // clamp physically valid spring length
        spring_length = Math::clamp(spring_length, 0.0f, wheel->m_resting_distnace);

        // compression only
        float compression = wheel->m_resting_distnace - spring_length;
        if (compression <= 0.0f) {
            wheel->set_normal_force(0.0f);
            continue;
        }

        Node3D *wheel_mesh = wheel->get_node<Node3D>("wheel");
        Vector3 mesh_target = wheel_mesh->get_position();
        mesh_target.y = - spring_length;
        wheel_mesh->set_position(mesh_target);

        float spring_force = wheel->m_spring_strength * compression;

        Vector3 world_velocity = get_linear_velocity() + get_angular_velocity().cross(contact - get_global_position());
        float relative_velocity = up_direction.dot(world_velocity);
        float spring_damp_force = relative_velocity * wheel->m_spring_damping;
        float normal_force = Math::max(0.0f, spring_force - spring_damp_force);

        wheel->set_normal_force(normal_force);

        Vector3 force_vector = up_direction * (spring_force - spring_damp_force);
        Vector3 force_position_offset = contact - get_global_position();
        apply_force(force_vector, force_position_offset);
    }
}

void MoVeCar::update_acceleration(float delta) {
    int powered = 0;
    float avg_omega = 0.0f; // rad/s

    for (auto &w : wheels) {
        if (!w->get_is_powered()) continue;
        powered++;
        avg_omega += w->get_angular_velocity();
    }
    if (powered == 0) return;

    avg_omega /= (float)powered;

    float gear = m_transmission->get_gear_ratio();
    if (gear == 0.0f) {
        m_engine->set_reflected_load(0.0f);
        return;
    }

    float target_rpm = Math::abs(avg_omega * gear) * (60.0f / Math_TAU);

    float rpm = (float)m_engine->get_current_rpm();
    float lock_strength = 12.0f;                  // tune 6..20
    float blend = 1.0f - Math::exp(-lock_strength * delta);

    float new_rpm = Math::lerp(rpm, target_rpm, blend);
    // If you have idle control, you can still clamp to >= 0 here safely
    m_engine->set_current_rpm(new_rpm);

    // --- Engine torque (Nm) at the now-locked RPM
    float throttle = (float)m_engine->get_throttle();
    float T_engine = (float)m_engine->engine_torque(new_rpm);

    // Driveshaft torque through gearing (Nm at wheels combined)
    float driveshaft_torque = T_engine * gear;
    float torque_per_wheel = driveshaft_torque / (float)powered;

    float total_wheel_load = 0.0f;

    for (auto &w : wheels) {
        if (!w->get_is_powered() || !w->is_colliding()) {
            if (w->get_is_powered()) w->set_normal_force(0.0f);
            continue;
        }

        Vector3 forward = -w->get_global_transform().get_basis().get_column(2);
        Vector3 contact = w->get_collision_point();
        Vector3 offset = contact - get_global_position();

        Vector3 contact_velocity = get_linear_velocity() + get_angular_velocity().cross(offset);
        float ground_speed = forward.dot(contact_velocity);

        w->set_ground_speed(ground_speed);
        w->set_drive_torque(torque_per_wheel);

        w->integrate(delta);

        Vector3 force = forward * w->get_longitudinal_force();
        apply_force(force, offset);

        total_wheel_load += Math::abs(w->get_reaction_torque());
    }

    float reflected = 0.0f;
    float gear_abs = Math::abs(gear);
    if (gear_abs > 0.001f) {
        reflected = total_wheel_load / gear_abs;
    }

    m_engine->set_reflected_load(reflected);
}

void MoVeCar::set_engine(Ref<MoVeEngine> value) {m_engine = value;}
Ref<MoVeEngine> MoVeCar::get_engine() const {return m_engine;}

void MoVeCar::set_transmission(Ref<MoVeTransmission> value) {m_transmission = value;}
Ref<MoVeTransmission> MoVeCar::get_transmission() const {return m_transmission;}

void MoVeCar::set_wheel_paths(const TypedArray<NodePath> &p_paths) {
    m_wheel_paths = p_paths;
    call_deferred("update_wheels");
}
TypedArray<NodePath> MoVeCar::get_wheel_paths() const { return m_wheel_paths; }

void MoVeCar::_bind_methods() {
    ClassDB::bind_method(D_METHOD("update"), &MoVeCar::update);
    ClassDB::bind_method(D_METHOD("update_wheels"), &MoVeCar::update_wheels);
    ClassDB::bind_method(D_METHOD("update_suspension"), &MoVeCar::update_suspension);
    ClassDB::bind_method(D_METHOD("update_acceleration"), &MoVeCar::update_acceleration);

	ClassDB::bind_method(D_METHOD("set_engine", "value"), &MoVeCar::set_engine);
    ClassDB::bind_method(D_METHOD("get_engine"), &MoVeCar::get_engine);
    ClassDB::bind_method(D_METHOD("set_transmission", "value"), &MoVeCar::set_transmission);
    ClassDB::bind_method(D_METHOD("get_transmission"), &MoVeCar::get_transmission);
    ClassDB::bind_method(D_METHOD("set_wheel_paths", "value"), &MoVeCar::set_wheel_paths);
    ClassDB::bind_method(D_METHOD("get_wheel_paths"), &MoVeCar::get_wheel_paths);

    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "engine", PROPERTY_HINT_RESOURCE_TYPE, "MoVeEngine"), "set_engine", "get_engine");
    ADD_PROPERTY(
        PropertyInfo(Variant::OBJECT, "transmission", PROPERTY_HINT_RESOURCE_TYPE, "MoVeTransmission"),
        "set_transmission",
        "get_transmission"
    );
    ADD_PROPERTY(
        PropertyInfo(Variant::ARRAY, "wheels", PROPERTY_HINT_ARRAY_TYPE, "NodePath"),
        "set_wheel_paths",
        "get_wheel_paths"
    );
}