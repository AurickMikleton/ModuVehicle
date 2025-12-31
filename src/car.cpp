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

void MoVeCar::update_acceleration(float dt) {
    int powered = 0;
    for (auto &w : wheels) if (w->get_is_powered()) powered++;
    if (powered == 0) return;

    float gear = m_transmission->get_gear_ratio();
    if (gear == 0.0f) return;

    // avg powered wheel omega -> turbine rpm
    float avg_omega = 0.0f;
    for (auto &w : wheels) {
        if (!w->get_is_powered()) continue;
        avg_omega += w->get_angular_velocity();
    }
    avg_omega /= (float)powered;

    float wheel_rpm = avg_omega * (60.0f / Math_TAU);
    float turbine_rpm = Math::abs(wheel_rpm * gear);

    float engine_rpm = m_engine->get_current_rpm();
    float throttle = m_engine->get_throttle();

    float T_engine = (float)m_engine->engine_torque(engine_rpm);
    float tc_mult = m_transmission->torque_converter_multiplier(engine_rpm, turbine_rpm, throttle);

    float driveshaft_torque = T_engine * tc_mult * gear;
    float torque_per_wheel = driveshaft_torque / (float)powered;

    float total_wheel_load = 0.0f;

    for (auto &w : wheels) {
        if (!w->get_is_powered() || !w->is_colliding()) continue;

        Vector3 forward = -w->get_global_transform().get_basis().get_column(2);
        Vector3 contact = w->get_collision_point();
        Vector3 r = contact - get_global_position();

        // ground speed at contact along forward
        Vector3 v_contact = get_linear_velocity() + get_angular_velocity().cross(r);
        float ground_speed = forward.dot(v_contact);

        w->set_ground_speed(ground_speed);
        w->set_drive_torque(torque_per_wheel);

        // If you don’t yet compute normal force, you MUST provide something nonzero,
        // or you’ll get 0 grip.
        // Start simple:
        // w->set_normal_force( (get_mass() * 9.81f) / wheels.size() );

        w->integrate(dt);

        

        Vector3 force = forward * w->get_longitudinal_force();
        apply_force(force, r);

        total_wheel_load += Math::abs(w->get_reaction_torque());
    }

    float reflected = m_transmission->reflect_wheel_load_to_engine(
        total_wheel_load, engine_rpm, turbine_rpm, throttle
    );

    // add baseline driveline drag reflected to engine
    reflected += m_transmission->get_reflected_load(engine_rpm, throttle);

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