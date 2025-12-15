#include "transmission.hpp"

float MoVeTransmission::driveshaft_torque(float T_engine, float rpm, float throttle) const {
    float gear = (float) gear_ratios[current_gear] * final_drive;
    if (gear == 0.0f) return 0.0f;

    // torque converter slip
    float slip = Math::clamp(rpm / tc_stall_rpm, 0.0f, 1.0f);
    float tc_mult = Math::lerp(1.0f, tc_max_mult, slip);

    // lockup
    if (rpm > tc_lockup_rpm && throttle < 0.8f)
        tc_mult = 1.0f;

    return T_engine * tc_mult * gear;
}

float MoVeTransmission::get_reflected_load(float rpm, float throttle) const {
    float gear = (float) gear_ratios[current_gear] * final_drive;
    if (gear == 0.0f) return 0.0f;

    float slip = Math::clamp(rpm / tc_stall_rpm, 0.0f, 1.0f);
    float tc_mult = Math::lerp(1.0f, tc_max_mult, slip);

    if (rpm > tc_lockup_rpm && throttle < 0.8f)
        tc_mult = 1.0f;

    return driveline_load / (Math::abs(gear) * tc_mult);
}

void MoVeTransmission::shift_down() {
    current_gear = Math::max(current_gear - 1, 0);
}

void MoVeTransmission::shift_up() {
    current_gear = Math::min(current_gear + 1, (int) gear_ratios.size() - 1);
}

int MoVeTransmission::get_current_gear() const { return current_gear; }

MoVeTransmission::MoVeTransmission() {
    gear_ratios = Array::make(-2.9, 0.0, 3.2, 2.1, 1.4, 1.0);
}

void MoVeTransmission::set_gear_ratios(const Array &value) { gear_ratios = value; }
Array MoVeTransmission::get_gear_ratios() const { return gear_ratios; }

void MoVeTransmission::_bind_methods() {
    ClassDB::bind_method(D_METHOD("driveshaft_torque", "engine_torque", "engine_rpm", "throttle"),
        &MoVeTransmission::driveshaft_torque);
    ClassDB::bind_method(D_METHOD("get_reflected_load", "engine_rpm", "throttle"),
        &MoVeTransmission::get_reflected_load);

    ClassDB::bind_method(D_METHOD("shift_up"), &MoVeTransmission::shift_up);
    ClassDB::bind_method(D_METHOD("shift_down"), &MoVeTransmission::shift_down);

    ClassDB::bind_method(D_METHOD("get_current_gear"), &MoVeTransmission::get_current_gear);
    
    ClassDB::bind_method(D_METHOD("set_gear_ratios", "value"), &MoVeTransmission::set_gear_ratios);
    ClassDB::bind_method(D_METHOD("get_gear_ratios"), &MoVeTransmission::get_gear_ratios);

    ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "gear_ratios"), "set_gear_ratios", "get_gear_ratios");
}