#include "engine_spec.hpp"

namespace godot {

EngineSpec::EngineSpec() {
    torque_samples.push_back(0.5531915f);
    torque_samples.push_back(0.7234043f);
    torque_samples.push_back(0.8723404f);
    torque_samples.push_back(0.9680851f);
    torque_samples.push_back(1.0f);
    torque_samples.push_back(0.9574468f);
    torque_samples.push_back(0.8617021f);
}

void EngineSpec::_bind_methods() {
    ADD_PROPERTY(PropertyInfo(Variant::NIL, "Identity", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_CATEGORY), "", "");

    ClassDB::bind_method(D_METHOD("set_display_name", "value"), &EngineSpec::set_display_name);
    ClassDB::bind_method(D_METHOD("get_display_name"), &EngineSpec::get_display_name);
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "display_name"), "set_display_name", "get_display_name");

    ADD_PROPERTY(PropertyInfo(Variant::NIL, "Operating range", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_CATEGORY), "", "");

    ClassDB::bind_method(D_METHOD("set_idle_rpm", "value"), &EngineSpec::set_idle_rpm);
    ClassDB::bind_method(D_METHOD("get_idle_rpm"), &EngineSpec::get_idle_rpm);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "idle_rpm", PROPERTY_HINT_RANGE, "300,2000,10"), "set_idle_rpm", "get_idle_rpm");

    ClassDB::bind_method(D_METHOD("set_redline_rpm", "value"), &EngineSpec::set_redline_rpm);
    ClassDB::bind_method(D_METHOD("get_redline_rpm"), &EngineSpec::get_redline_rpm);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "redline_rpm", PROPERTY_HINT_RANGE, "2000,15000,50"), "set_redline_rpm", "get_redline_rpm");

    ClassDB::bind_method(D_METHOD("set_rotational_inertia", "value"), &EngineSpec::set_rotational_inertia);
    ClassDB::bind_method(D_METHOD("get_rotational_inertia"), &EngineSpec::get_rotational_inertia);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "rotational_inertia", PROPERTY_HINT_RANGE, "0.05,2,0.01"), "set_rotational_inertia", "get_rotational_inertia");

    ClassDB::bind_method(D_METHOD("set_friction_nm", "value"), &EngineSpec::set_friction_nm);
    ClassDB::bind_method(D_METHOD("get_friction_nm"), &EngineSpec::get_friction_nm);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "friction_nm", PROPERTY_HINT_RANGE, "0,500,1"), "set_friction_nm", "get_friction_nm");

    ClassDB::bind_method(D_METHOD("set_engine_braking_nm", "value"), &EngineSpec::set_engine_braking_nm);
    ClassDB::bind_method(D_METHOD("get_engine_braking_nm"), &EngineSpec::get_engine_braking_nm);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "engine_braking_nm", PROPERTY_HINT_RANGE, "0,300,1"), "set_engine_braking_nm", "get_engine_braking_nm");

    ClassDB::bind_method(D_METHOD("set_engine_braking_exponent", "value"), &EngineSpec::set_engine_braking_exponent);
    ClassDB::bind_method(D_METHOD("get_engine_braking_exponent"), &EngineSpec::get_engine_braking_exponent);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "engine_braking_exponent", PROPERTY_HINT_RANGE, "0.5,3,0.05"), "set_engine_braking_exponent", "get_engine_braking_exponent");

    ADD_PROPERTY(PropertyInfo(Variant::NIL, "Torque curve", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_CATEGORY), "", "");

    ClassDB::bind_method(D_METHOD("set_torque_samples", "value"), &EngineSpec::set_torque_samples);
    ClassDB::bind_method(D_METHOD("get_torque_samples"), &EngineSpec::get_torque_samples);
    ADD_PROPERTY(PropertyInfo(Variant::PACKED_FLOAT32_ARRAY, "torque_samples"), "set_torque_samples", "get_torque_samples");

    ClassDB::bind_method(D_METHOD("set_peak_torque_nm", "value"), &EngineSpec::set_peak_torque_nm);
    ClassDB::bind_method(D_METHOD("get_peak_torque_nm"), &EngineSpec::get_peak_torque_nm);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "peak_torque_nm", PROPERTY_HINT_RANGE, "1,5000,1"), "set_peak_torque_nm", "get_peak_torque_nm");

    ClassDB::bind_method(D_METHOD("set_torque_multiplier", "value"), &EngineSpec::set_torque_multiplier);
    ClassDB::bind_method(D_METHOD("get_torque_multiplier"), &EngineSpec::get_torque_multiplier);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "torque_multiplier", PROPERTY_HINT_RANGE, "0,10,0.05"), "set_torque_multiplier", "get_torque_multiplier");

    ADD_PROPERTY(PropertyInfo(Variant::NIL, "Forced induction", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_CATEGORY), "", "");

    ClassDB::bind_method(D_METHOD("set_turbocharged", "value"), &EngineSpec::set_turbocharged);
    ClassDB::bind_method(D_METHOD("get_turbocharged"), &EngineSpec::get_turbocharged);
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "turbocharged"), "set_turbocharged", "get_turbocharged");

    ClassDB::bind_method(D_METHOD("set_max_boost_bar", "value"), &EngineSpec::set_max_boost_bar);
    ClassDB::bind_method(D_METHOD("get_max_boost_bar"), &EngineSpec::get_max_boost_bar);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "max_boost_bar", PROPERTY_HINT_RANGE, "0,2,0.01"), "set_max_boost_bar", "get_max_boost_bar");

    ClassDB::bind_method(D_METHOD("set_boost_threshold_rpm", "value"), &EngineSpec::set_boost_threshold_rpm);
    ClassDB::bind_method(D_METHOD("get_boost_threshold_rpm"), &EngineSpec::get_boost_threshold_rpm);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "boost_threshold_rpm", PROPERTY_HINT_RANGE, "500,8000,50"), "set_boost_threshold_rpm", "get_boost_threshold_rpm");

    ADD_PROPERTY(PropertyInfo(Variant::NIL, "Supercharger physics", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_CATEGORY), "", "");

    ClassDB::bind_method(D_METHOD("set_supercharger_type", "value"), &EngineSpec::set_supercharger_type);
    ClassDB::bind_method(D_METHOD("get_supercharger_type"), &EngineSpec::get_supercharger_type);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "supercharger_type", PROPERTY_HINT_ENUM, "None,Roots,Centrifugal"), "set_supercharger_type", "get_supercharger_type");

    ClassDB::bind_method(D_METHOD("set_supercharger_max_boost_bar", "value"), &EngineSpec::set_supercharger_max_boost_bar);
    ClassDB::bind_method(D_METHOD("get_supercharger_max_boost_bar"), &EngineSpec::get_supercharger_max_boost_bar);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "supercharger_max_boost_bar", PROPERTY_HINT_RANGE, "0,2,0.01"), "set_supercharger_max_boost_bar", "get_supercharger_max_boost_bar");

    ClassDB::bind_method(D_METHOD("set_roots_low_rpm_boost_fraction", "value"), &EngineSpec::set_roots_low_rpm_boost_fraction);
    ClassDB::bind_method(D_METHOD("get_roots_low_rpm_boost_fraction"), &EngineSpec::get_roots_low_rpm_boost_fraction);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "roots_low_rpm_boost_fraction", PROPERTY_HINT_RANGE, "0,1,0.01"), "set_roots_low_rpm_boost_fraction", "get_roots_low_rpm_boost_fraction");

    ClassDB::bind_method(D_METHOD("set_supercharger_charge_efficiency", "value"), &EngineSpec::set_supercharger_charge_efficiency);
    ClassDB::bind_method(D_METHOD("get_supercharger_charge_efficiency"), &EngineSpec::get_supercharger_charge_efficiency);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "supercharger_charge_efficiency", PROPERTY_HINT_RANGE, "0,1,0.01"), "set_supercharger_charge_efficiency", "get_supercharger_charge_efficiency");

    ClassDB::bind_method(D_METHOD("set_supercharger_drive_loss_kw", "value"), &EngineSpec::set_supercharger_drive_loss_kw);
    ClassDB::bind_method(D_METHOD("get_supercharger_drive_loss_kw"), &EngineSpec::get_supercharger_drive_loss_kw);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "supercharger_drive_loss_kw", PROPERTY_HINT_RANGE, "0,150,0.5"), "set_supercharger_drive_loss_kw", "get_supercharger_drive_loss_kw");

}

void EngineSpec::set_display_name(const String &value) {
    if (display_name == value) return;
    display_name = value;
    emit_changed();
}

String EngineSpec::get_display_name() const {
    return display_name;
}

void EngineSpec::set_idle_rpm(double value) {
    if (idle_rpm == value) return;
    idle_rpm = value;
    emit_changed();
}

double EngineSpec::get_idle_rpm() const {
    return idle_rpm;
}

void EngineSpec::set_redline_rpm(double value) {
    if (redline_rpm == value) return;
    redline_rpm = value;
    emit_changed();
}

double EngineSpec::get_redline_rpm() const {
    return redline_rpm;
}

void EngineSpec::set_rotational_inertia(double value) {
    if (rotational_inertia == value) return;
    rotational_inertia = value;
    emit_changed();
}

double EngineSpec::get_rotational_inertia() const {
    return rotational_inertia;
}

void EngineSpec::set_friction_nm(double value) {
    if (friction_nm == value) return;
    friction_nm = value;
    emit_changed();
}

double EngineSpec::get_friction_nm() const {
    return friction_nm;
}

void EngineSpec::set_engine_braking_nm(double value) {
    if (engine_braking_nm == value) return;
    engine_braking_nm = value;
    emit_changed();
}

double EngineSpec::get_engine_braking_nm() const {
    return engine_braking_nm;
}

void EngineSpec::set_engine_braking_exponent(double value) {
    if (engine_braking_exponent == value) return;
    engine_braking_exponent = value;
    emit_changed();
}

double EngineSpec::get_engine_braking_exponent() const {
    return engine_braking_exponent;
}

void EngineSpec::set_torque_samples(const PackedFloat32Array &value) {
    torque_samples = value;
    emit_changed();
}

PackedFloat32Array EngineSpec::get_torque_samples() const {
    return torque_samples;
}

void EngineSpec::set_peak_torque_nm(double value) {
    if (peak_torque_nm == value) return;
    peak_torque_nm = value;
    emit_changed();
}

double EngineSpec::get_peak_torque_nm() const {
    return peak_torque_nm;
}

void EngineSpec::set_torque_multiplier(double value) {
    if (torque_multiplier == value) return;
    torque_multiplier = value;
    emit_changed();
}

double EngineSpec::get_torque_multiplier() const {
    return torque_multiplier;
}

void EngineSpec::set_turbocharged(bool value) {
    if (turbocharged == value) return;
    turbocharged = value;
    emit_changed();
}

bool EngineSpec::get_turbocharged() const {
    return turbocharged;
}

void EngineSpec::set_max_boost_bar(double value) {
    if (max_boost_bar == value) return;
    max_boost_bar = value;
    emit_changed();
}

double EngineSpec::get_max_boost_bar() const {
    return max_boost_bar;
}

void EngineSpec::set_boost_threshold_rpm(double value) {
    if (boost_threshold_rpm == value) return;
    boost_threshold_rpm = value;
    emit_changed();
}

double EngineSpec::get_boost_threshold_rpm() const {
    return boost_threshold_rpm;
}

void EngineSpec::set_supercharger_type(int64_t value) {
    if (supercharger_type == value) return;
    supercharger_type = value;
    emit_changed();
}

int64_t EngineSpec::get_supercharger_type() const {
    return supercharger_type;
}

void EngineSpec::set_supercharger_max_boost_bar(double value) {
    if (supercharger_max_boost_bar == value) return;
    supercharger_max_boost_bar = value;
    emit_changed();
}

double EngineSpec::get_supercharger_max_boost_bar() const {
    return supercharger_max_boost_bar;
}

void EngineSpec::set_roots_low_rpm_boost_fraction(double value) {
    if (roots_low_rpm_boost_fraction == value) return;
    roots_low_rpm_boost_fraction = value;
    emit_changed();
}

double EngineSpec::get_roots_low_rpm_boost_fraction() const {
    return roots_low_rpm_boost_fraction;
}

void EngineSpec::set_supercharger_charge_efficiency(double value) {
    if (supercharger_charge_efficiency == value) return;
    supercharger_charge_efficiency = value;
    emit_changed();
}

double EngineSpec::get_supercharger_charge_efficiency() const {
    return supercharger_charge_efficiency;
}

void EngineSpec::set_supercharger_drive_loss_kw(double value) {
    if (supercharger_drive_loss_kw == value) return;
    supercharger_drive_loss_kw = value;
    emit_changed();
}

double EngineSpec::get_supercharger_drive_loss_kw() const {
    return supercharger_drive_loss_kw;
}

} // namespace godot

