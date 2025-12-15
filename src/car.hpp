#pragma once

#include "godot_cpp/classes/rigid_body3d.hpp"
#include "godot_cpp/classes/wrapped.hpp"
#include "godot_cpp/variant/variant.hpp"
#include "godot_cpp/classes/ref.hpp"

#include "components/engine.hpp"

using namespace godot;

class MoVeCar : public RigidBody3D {
private:
    GDCLASS(MoVeCar, RigidBody3D);
	Ref<MoVeEngine> m_engine;
	bool m_aero_enabled;
	double m_aero_up_force;
	double m_aero_down_force;
protected:
    static void _bind_methods();
public:
    MoVeCar();
    void aerodynamics() const;
	void _physics_process(double delta) override;

	void set_aero_enabled(bool value); bool get_aero_enabled() const;
	void set_aero_up_force(double value); double get_aero_up_force() const;
	void set_aero_down_force(double value); double get_aero_down_force() const;

	void set_engine(Ref<MoVeEngine> value); Ref<MoVeEngine> get_engine() const;
};
