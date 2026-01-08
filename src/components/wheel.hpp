#pragma once

#include "godot_cpp/classes/ray_cast3d.hpp"
#include "godot_cpp/classes/wrapped.hpp"

using namespace godot;

class MoVeWheel : public RayCast3D {
public:
    float m_spring_strength = 100.0f;
    float m_spring_damping = 2.0f;
    float m_resting_distnace = 0.5f;
    float m_wheel_radius = 0.4f;
    bool m_is_powered = false;
    // rotation
    float m_angular_velocity = 0.0f; // rad/s
    float m_ground_speed = 0.0f;
    float m_inertia = 1.2f; // kg * m^2
    // tire
    float m_normal_force = 0.0f; // N
    float m_mu = 1.2f; // friction coefficient
    // inputs
    float m_drive_torque = 0.0f; // Nm
    float m_brake_torque = 0.0f; // Nm
    // outputs
    float m_reaction_torque = 0.0f;  // Nm
    float m_long_force = 0.0f;       // N


    GDCLASS(MoVeWheel, RayCast3D);
protected:
    static void _bind_methods();
public:
    float get_resistance_torque() const;
    void integrate(float delta);

    void set_drive_torque(float t);
    void set_brake_torque(float t);

    void set_ground_speed(float v_mps); float get_ground_speed() const; // forward speed at contact (m/s)
    float get_angular_velocity() const;   // rad/s

    float get_longitudinal_force() const;
    float get_reaction_torque() const;

    void set_normal_force(float f);

    void set_is_powered(bool v); bool get_is_powered() const;
    void set_spring_strength(float v); float get_spring_strength() const;
    void set_spring_damping(float v); float get_spring_damping() const;
    void set_resting_distnace(float v); float get_resting_distnace() const;
    void set_wheel_radius(float v); float get_wheel_radius() const;
};