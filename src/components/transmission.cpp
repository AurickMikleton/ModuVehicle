#include "transmission.hpp"

float MoVeTransmission::driveshaft_torque(float T_engine, float engine_rpm, float throttle) const {
    float gear = get_gear_ratio();
    if (gear == 0.0f) return 0.0f;

    // NOTE: this overload assumes turbine_rpm is unknown; keep for compatibility
    // Treat turbine_rpm ~ engine_rpm at speed, but at launch give stall behavior:
    float turbine_rpm = Math::min(engine_rpm, tc_stall_rpm);
    float tc_mult = torque_converter_multiplier(engine_rpm, turbine_rpm, throttle);

    return T_engine * tc_mult * gear;
}

float MoVeTransmission::get_reflected_load(float engine_rpm, float throttle) const {
    float gear = get_gear_ratio();
    if (gear == 0.0f) return 0.0f;

    // approximate converter mult using stall assumption
    float turbine_rpm = Math::min(engine_rpm, tc_stall_rpm);
    float tc_mult = torque_converter_multiplier(engine_rpm, turbine_rpm, throttle);

    return driveline_load / (Math::abs(gear) * tc_mult);
}

float MoVeTransmission::get_gear_ratio() const {
    if (gear_ratios.is_empty()) return 0.0f;
    float gear = (float)gear_ratios[current_gear];
    return gear * final_drive;
}

float MoVeTransmission::torque_converter_multiplier(float engine_rpm, float turbine_rpm, float throttle) const {
    // slip based on speed difference
    float slip = 0.0f;
    if (engine_rpm > 50.0f) {
        slip = (engine_rpm - turbine_rpm) / engine_rpm;
        slip = Math::clamp(slip, 0.0f, 1.0f);
    }

    // tc_max_mult at stall -> 1.0 near lock
    float mult = Math::lerp(tc_max_mult, 1.0f, 1.0f - slip);

    // lock-up clutch when nearly coupled
    if (engine_rpm > tc_lockup_rpm && slip < 0.05f && throttle < 0.8f)
        mult = 1.0f;

    return mult;
}

float MoVeTransmission::torque_converter_coupling(float engine_rpm, float turbine_rpm) const {
    // 0 when turbine stalled, 1 when nearly coupled
    if (engine_rpm < 50.0f) return 0.0f;
    float ratio = turbine_rpm / engine_rpm;
    return Math::clamp(ratio, 0.0f, 1.0f);
}

float MoVeTransmission::reflect_wheel_load_to_engine(
    float wheel_load_torque,
    float engine_rpm,
    float turbine_rpm,
    float throttle
) const {
    float gear = get_gear_ratio();
    if (gear == 0.0f) return 0.0f;

    float tc_mult = torque_converter_multiplier(engine_rpm, turbine_rpm, throttle);
    float coupling = torque_converter_coupling(engine_rpm, turbine_rpm);

    float reflected = (Math::abs(wheel_load_torque) / (Math::abs(gear) * tc_mult)) * coupling;

    // ERR_PRINT(std::to_string(reflected).c_str());
    // cap reflected load during high slip
    if (coupling < 0.3f)
         reflected = Math::min(reflected, 150.0f); // tune

    return Math::max(reflected, 0.0f);
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