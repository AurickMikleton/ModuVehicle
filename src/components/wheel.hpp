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
    GDCLASS(MoVeWheel, RayCast3D);
protected:
    static void _bind_methods();
public:
    MoVeWheel() = default;
    void update_suspension();

    void set_is_powered(bool v); bool get_is_powered() const;
    void set_spring_strength(float v); float get_spring_strength() const;
    void set_spring_damping(float v); float get_spring_damping() const;
    void set_resting_distnace(float v); float get_resting_distnace() const;
    void set_wheel_radius(float v); float get_wheel_radius() const;
};