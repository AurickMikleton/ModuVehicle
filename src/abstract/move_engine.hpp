#pragma once

#include "godot_cpp/classes/resource.hpp"
#include "godot_cpp/classes/wrapped.hpp"

using namespace godot;

class MoVeEngine : public Resource {
	GDCLASS(MoVeEngine, Resource);

protected:
	static void _bind_methods() {}

public:
	virtual double engine_torque(double rpm) = 0;
	virtual void update_rpm(double delta) = 0;
	virtual void set_reflected_load(double v) = 0;

	virtual double get_throttle() const = 0;
	virtual void set_throttle(double value) = 0;

	virtual double get_idle_rpm() const = 0;

	virtual double get_current_rpm() const = 0;
	virtual void set_current_rpm(double value) = 0;
};
