#pragma once

#include "godot_cpp/classes/rigid_body3d.hpp"
#include "godot_cpp/classes/wrapped.hpp"
#include "godot_cpp/variant/variant.hpp"
#include "godot_cpp/classes/ref.hpp"

#include "components/engine.hpp"
#include "components/transmission.hpp"

using namespace godot;

class MoVeCar : public RigidBody3D {
private:
    GDCLASS(MoVeCar, RigidBody3D);
	Ref<MoVeEngine> m_engine;
	Ref<MoVeTransmission> m_transmission;
protected:
    static void _bind_methods();
public:
	void set_engine(Ref<MoVeEngine> value); Ref<MoVeEngine> get_engine() const;
	void set_transmission(Ref<MoVeTransmission> value); Ref<MoVeTransmission> get_transmission() const;
};
