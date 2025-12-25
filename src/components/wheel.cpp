#include "wheel.hpp"

void MoVeWheel::integrate(float delta) {
    float rolling_torque = 0.015f * m_normal_force * m_wheel_radius;

    float max_tire_force = m_mu * m_normal_force;
    m_long_force = Math::clamp(
        m_angular_velocity * m_wheel_radius * 50.0f,
        -max_tire_force,
        max_tire_force
    );

    float tire_torque = m_long_force * m_wheel_radius;

    float net_torque =
        m_drive_torque
        - tire_torque
        - rolling_torque
        - m_brake_torque;
    
    float alpha = net_torque / m_inertia;
    m_angular_velocity += alpha * delta;

    m_reaction_torque = tire_torque + rolling_torque;
}

void MoVeWheel::set_drive_torque(float t) {
    m_drive_torque = m_is_powered ? t : 0.0f;
}

void MoVeWheel::set_brake_torque(float t) {
    m_brake_torque = t;
}

void MoVeWheel::set_normal_force(float f) {
    m_normal_force = Math::max(f, 0.0f);
}

float MoVeWheel::get_longitudinal_force() const {
    return m_long_force;
}

float MoVeWheel::get_reaction_torque() const {
    return m_reaction_torque;
}

float MoVeWheel::get_angular_velocity() const {
    return m_angular_velocity;
}

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