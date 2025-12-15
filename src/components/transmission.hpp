#pragma once

#include "godot_cpp/classes/resource.hpp"
#include "godot_cpp/classes/wrapped.hpp"
#include "godot_cpp/variant/variant.hpp"

#include "godot_cpp/variant/utility_functions.hpp"

using namespace godot;

class MoVeTransmission : public Resource {
private:
    GDCLASS(MoVeTransmission, Resource); // maybe, this class might be abstract
    float gear_ratios[6]; // R N 1 2 3 4
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
    float driveshaft_torque(float T_engine, float rpm, float throttle) const;
    float get_reflected_load(float rpm, float throttle) const;
};