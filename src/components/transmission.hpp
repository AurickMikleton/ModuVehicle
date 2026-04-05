#pragma once

#include "godot_cpp/classes/resource.hpp"
#include "godot_cpp/classes/wrapped.hpp"
#include "godot_cpp/variant/variant.hpp"

#include "godot_cpp/variant/utility_functions.hpp"

using namespace godot;

class MoVeTransmission : public Resource {
private:
	GDCLASS(MoVeTransmission, Resource); // maybe, this class might be abstract
	TypedArray<float> m_gear_ratios; // R N 1 2 3 4
	int m_current_gear = 2;
	float m_final_drive = 3.7f;

	// Legacy block; delete when possible
	float m_couple_k = 20.0f; // Nm per (rad/s) slip
	float m_couple_max = 300.0f; // Nm clamp
	float m_lock_slip_rads = 2.0f; // lock when slip small (rad/s)
	float m_lock_min_rpm = 1200.0f;

	// centrifugal clutch
	float m_clutch_engage_rpm = 1400.0f; // starts biting
	float m_clutch_full_rpm = 2800.0f; // fully clamped
	float m_clutch_max_torque = 450.0f; // Nm max transferable
	float m_clutch_k = 8.0f; // slip -> torque gain
protected:
	static void _bind_methods();

public:
	MoVeTransmission();

	void shift_up();
	void shift_down();

	bool should_lock(float engine_rpm, float slip_omega, float throttle) const;
	float coupling_torque(float slip_omega) const;

	float get_gear_ratio() const; // includes final drive, signed
	int get_current_gear() const;
	void set_gear_ratios(const TypedArray<float> &value);
	TypedArray<float> get_gear_ratios() const;
	void set_final_drive(float value);
	float get_final_drive() const;
};
