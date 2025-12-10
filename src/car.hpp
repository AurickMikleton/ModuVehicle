#pragma once

#include "godot_cpp/classes/rigid_body3d.hpp"
#include "godot_cpp/classes/wrapped.hpp"

using namespace godot;

class MoVeCar : public RigidBody3D {
private:
    GDCLASS(MoVeCar, RigidBody3D);
    float m_crank_shaft_rpm = 0.0;
    float m_transmission_rpm = 0.0;
protected:
    static void _bind_methods();
public:
    MoVeCar() = default;
    void aerodynamics() const;
    float get_crank_rpm() const;
};