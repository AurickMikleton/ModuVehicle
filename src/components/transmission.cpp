#include "transmission.hpp"

MoVeTransmission::MoVeTransmission() {
    gear_ratios[0] = -2.9f;
    gear_ratios[1] = 0.0f;
    gear_ratios[2] = 3.2f;
    gear_ratios[3] = 2.1f;
    gear_ratios[4] = 1.4f;
    gear_ratios[5] = 1.0f;
}

void MoVeTransmission::_bind_methods() {
    ClassDB::bind_method(D_METHOD("driveshaft_torque", "engine_torque", "engine_rpm", "throttle"),
        &MoVeTransmission::driveshaft_torque);
    ClassDB::bind_method(D_METHOD("get_reflected_load", "engine_rpm", "throttle"),
        &MoVeTransmission::get_reflected_load);
}

float MoVeTransmission::driveshaft_torque(float T_engine, float rpm, float throttle) const {
    float gear = gear_ratios[current_gear] * final_drive;
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
    float gear = gear_ratios[current_gear] * final_drive;
    if (gear == 0.0f) return 0.0f;

    float slip = Math::clamp(rpm / tc_stall_rpm, 0.0f, 1.0f);
    float tc_mult = Math::lerp(1.0f, tc_max_mult, slip);

    if (rpm > tc_lockup_rpm && throttle < 0.8f)
        tc_mult = 1.0f;

    return driveline_load / (Math::abs(gear) * tc_mult);
}