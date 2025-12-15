#pragma once

#include "godot_cpp/classes/ray_cast3d.hpp"
#include "godot_cpp/classes/wrapped.hpp"

using namespace godot;

class MoVeWheel : public RayCast3D {
private:
    bool m_steering;
    GDCLASS(MoVeWheel, RayCast3D);
protected:
    static void _bind_methods();
public:
    MoVeWheel() = default;
    bool get_steering() const;
};