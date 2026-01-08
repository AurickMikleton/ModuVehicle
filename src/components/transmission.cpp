#include "transmission.hpp"

float MoVeTransmission::get_gear_ratio() const {
    if (m_gear_ratios.is_empty()) return 0.0f;
    float gear = (float) m_gear_ratios[m_current_gear];
    return gear * m_final_drive;
}

bool MoVeTransmission::should_lock(float engine_rpm, float slip_omega, float throttle) const {
    if (engine_rpm < m_lock_min_rpm) return false;
    if (throttle > 0.3f) return false; // only lock at light throttle
    return Math::abs(slip_omega) < m_lock_slip_rads;
}

float MoVeTransmission::coupling_torque(float slip_omega) const {
    float T = m_couple_k * slip_omega;
    return Math::clamp(T, -m_couple_max, m_couple_max);
}

void MoVeTransmission::shift_down() {
    m_current_gear = Math::max(m_current_gear - 1, 0);
}

void MoVeTransmission::shift_up() {
    m_current_gear = Math::min(m_current_gear + 1, (int) m_gear_ratios.size() - 1);
}

int MoVeTransmission::get_current_gear() const { return m_current_gear; }

void MoVeTransmission::set_gear_ratios(const TypedArray<float> &value) { m_gear_ratios = value; }
TypedArray<float> MoVeTransmission::get_gear_ratios() const { return m_gear_ratios; }

void MoVeTransmission::set_final_drive(float value) { m_final_drive = value; }
float MoVeTransmission::get_final_drive() const { return m_final_drive; }

MoVeTransmission::MoVeTransmission() {
    m_gear_ratios.clear();
    m_gear_ratios.resize(6);

    m_gear_ratios[0] = -2.9f; // Reverse
    m_gear_ratios[1] =  0.0f; // Neutral
    m_gear_ratios[2] =  3.2f; // 1st
    m_gear_ratios[3] =  2.1f; // 2nd
    m_gear_ratios[4] =  1.4f; // 3rd
    m_gear_ratios[5] =  1.0f; // 4th
}

void MoVeTransmission::_bind_methods() {
    ClassDB::bind_method(D_METHOD("shift_up"), &MoVeTransmission::shift_up);
    ClassDB::bind_method(D_METHOD("shift_down"), &MoVeTransmission::shift_down);

    ClassDB::bind_method(D_METHOD("get_current_gear"), &MoVeTransmission::get_current_gear);
    
    ClassDB::bind_method(D_METHOD("set_gear_ratios", "value"), &MoVeTransmission::set_gear_ratios);
    ClassDB::bind_method(D_METHOD("get_gear_ratios"), &MoVeTransmission::get_gear_ratios);

    ClassDB::bind_method(D_METHOD("set_final_drive", "value"), &MoVeTransmission::set_final_drive);
    ClassDB::bind_method(D_METHOD("get_final_drive"), &MoVeTransmission::get_final_drive);

    ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "gear_ratios", PROPERTY_HINT_ARRAY_TYPE, "float"),
             "set_gear_ratios", "get_gear_ratios");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "final_drive"),
             "set_final_drive", "get_final_drive");
}