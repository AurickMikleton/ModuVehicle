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
        if (!wheel->is_colliding()) return;

        Vector3 contact = wheel->get_collision_point();
        Vector3 up_direction = wheel->get_global_transform().get_basis().get_column(1);
        float spring_length = wheel->get_global_position().distance_to(contact);
        float offset = wheel->m_resting_distnace - spring_length;

        float spring_force = wheel->m_spring_strength * offset;
        Vector3 force_vector = up_direction * spring_force;
        Vector3 force_position_offset = contact - wheel->get_global_position();
        apply_force(force_vector, force_position_offset);
    }
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