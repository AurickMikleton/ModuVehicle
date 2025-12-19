#pragma once

#include "godot_cpp/classes/ray_cast3d.hpp"
#include "godot_cpp/classes/wrapped.hpp"

using namespace godot;

class MoVeWheel : public RayCast3D {
public:
    float m_spring_strength = 100.0f;
    float m_spring_damping = 2.0f;
    float m_resting_distnace = 0.5f;
    GDCLASS(MoVeWheel, RayCast3D);
protected:
    static void _bind_methods();
public:
    MoVeWheel() = default;
    void update_suspension();
};