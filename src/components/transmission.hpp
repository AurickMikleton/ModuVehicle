#pragma once

#include "godot_cpp/classes/resource.hpp"
#include "godot_cpp/classes/wrapped.hpp"
#include "godot_cpp/variant/variant.hpp"

#include "godot_cpp/variant/utility_functions.hpp"

using namespace godot;

class MoVeTransmission : public Resource {
private:
    GDCLASS(MoVeTransmission, Resource); // maybe, this class might be abstract
    Array gear_ratios; // R N 1 2 3 4
    int current_gear = 2;
    float final_drive = 3.7f;
    // torque converter
    float tc_stall_rpm = 2800.0f;
    float tc_max_mult = 2.2f;
    float tc_lockup_rpm = 4200.0f;

    float driveline_load = 60.0f; // Nm base resistance
protected:
    static void _bind_methods();
public:
    MoVeTransmission();
    void shift_up();
    void shift_down();
    float driveshaft_torque(float T_engine, float rpm, float throttle) const;
    float get_reflected_load(float rpm, float throttle) const;

    float get_gear_ratio() const; // includes final drive, signed
    float torque_converter_coupling(float engine_rpm, float turbine_rpm) const;
    float torque_converter_multiplier(float engine_rpm, float turbine_rpm, float throttle) const;
    float reflect_wheel_load_to_engine(float wheel_load_torque, float engine_rpm, float turbine_rpm, float throttle) const;

    int get_current_gear() const;
    void set_gear_ratios(const Array &value); Array get_gear_ratios() const;
};