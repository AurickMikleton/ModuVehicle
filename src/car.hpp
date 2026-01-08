#pragma once

#include "godot_cpp/classes/rigid_body3d.hpp"
#include "godot_cpp/classes/wrapped.hpp"
#include "godot_cpp/variant/variant.hpp"
#include "godot_cpp/classes/ref.hpp"

#include "godot_cpp/classes/node3d.hpp"

#include "godot_cpp/classes/project_settings.hpp"

#include "components/engine.hpp"
#include "components/transmission.hpp"
#include "components/wheel.hpp"

#include <vector>

using namespace godot;

class MoVeCar : public RigidBody3D {
private:
    GDCLASS(MoVeCar, RigidBody3D);
	Ref<MoVeEngine> m_engine;
	Ref<MoVeTransmission> m_transmission;
	TypedArray<NodePath> m_wheel_paths;
	std::vector<MoVeWheel*> wheels;
protected:
    static void _bind_methods();
public:
	void update();
	void _ready() override;
	void update_wheels();
	void update_suspension(float delta);
	void update_acceleration(float delta);
	void update_traction(float delta);
	void set_engine(Ref<MoVeEngine> value); Ref<MoVeEngine> get_engine() const;
	void set_transmission(Ref<MoVeTransmission> value); Ref<MoVeTransmission> get_transmission() const;
	void set_wheel_paths(const TypedArray<NodePath> &p_paths); TypedArray<NodePath> get_wheel_paths() const;
};
