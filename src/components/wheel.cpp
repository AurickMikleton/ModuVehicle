#include "wheel.hpp"

void MoVeWheel::set_is_powered(bool v) { m_is_powered = v; }
bool MoVeWheel::get_is_powered() const { return m_is_powered; }

void MoVeWheel::set_spring_strength(float v) { m_spring_strength = v; }
float MoVeWheel::get_spring_strength() const { return m_spring_strength; }

void MoVeWheel::set_spring_damping(float v) { m_spring_damping = v; }
float MoVeWheel::get_spring_damping() const { return m_spring_damping; }

void MoVeWheel::set_resting_distnace(float v) { m_resting_distnace = v; }
float MoVeWheel::get_resting_distnace() const { return m_resting_distnace; }

void MoVeWheel::set_wheel_radius(float v) { m_wheel_radius = v; }
float MoVeWheel::get_wheel_radius() const { return m_wheel_radius; }

void MoVeWheel::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_is_powered", "value"), &MoVeWheel::set_is_powered);
    ClassDB::bind_method(D_METHOD("get_is_powered"), &MoVeWheel::get_is_powered);
    ClassDB::bind_method(D_METHOD("set_spring_strength", "value"), &MoVeWheel::set_spring_strength);
    ClassDB::bind_method(D_METHOD("get_spring_strength"), &MoVeWheel::get_spring_strength);
    ClassDB::bind_method(D_METHOD("set_spring_damping", "value"), &MoVeWheel::set_spring_damping);
    ClassDB::bind_method(D_METHOD("get_spring_damping"), &MoVeWheel::get_spring_damping);
    ClassDB::bind_method(D_METHOD("set_resting_distnace", "value"), &MoVeWheel::set_resting_distnace);
    ClassDB::bind_method(D_METHOD("get_resting_distnace"), &MoVeWheel::get_resting_distnace);
    ClassDB::bind_method(D_METHOD("set_wheel_radius", "value"), &MoVeWheel::set_wheel_radius);
    ClassDB::bind_method(D_METHOD("get_wheel_radius"), &MoVeWheel::get_wheel_radius);

    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "is_powered"), "set_is_powered", "get_is_powered");

    ADD_GROUP("properties", "");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "spring_strength"), "set_spring_strength", "get_spring_strength");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "spring_damping"), "set_spring_damping", "get_spring_damping");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "resting_distnace"), "set_resting_distnace", "get_resting_distnace");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "wheel_radius"), "set_wheel_radius", "get_wheel_radius");
}