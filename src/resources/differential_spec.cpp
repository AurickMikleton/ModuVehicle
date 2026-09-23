#include "differential_spec.hpp"

namespace godot {

DifferentialSpec::DifferentialSpec() {
}

void DifferentialSpec::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_display_name", "value"), &DifferentialSpec::set_display_name);
    ClassDB::bind_method(D_METHOD("get_display_name"), &DifferentialSpec::get_display_name);
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "display_name"),
        "set_display_name", "get_display_name");

    ClassDB::bind_method(D_METHOD("set_final_drive", "value"), &DifferentialSpec::set_final_drive);
    ClassDB::bind_method(D_METHOD("get_final_drive"), &DifferentialSpec::get_final_drive);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "final_drive", PROPERTY_HINT_RANGE, "1.0,8.0,0.01"),
        "set_final_drive", "get_final_drive");

    ClassDB::bind_method(D_METHOD("set_efficiency", "value"), &DifferentialSpec::set_efficiency);
    ClassDB::bind_method(D_METHOD("get_efficiency"), &DifferentialSpec::get_efficiency);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "efficiency", PROPERTY_HINT_RANGE, "0.0,1.0,0.01"),
        "set_efficiency", "get_efficiency");

    ClassDB::bind_method(D_METHOD("set_locking_strength", "value"), &DifferentialSpec::set_locking_strength);
    ClassDB::bind_method(D_METHOD("get_locking_strength"), &DifferentialSpec::get_locking_strength);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "locking_strength", PROPERTY_HINT_RANGE, "0.0,1.0,0.01"),
        "set_locking_strength", "get_locking_strength");

}

void DifferentialSpec::set_display_name(const String &value) {
    if (display_name == value) {
        return;
    }
    display_name = value;
    emit_changed();
}

String DifferentialSpec::get_display_name() const {
    return display_name;
}

void DifferentialSpec::set_final_drive(double value) {
    if (final_drive == value) {
        return;
    }
    final_drive = value;
    emit_changed();
}

double DifferentialSpec::get_final_drive() const {
    return final_drive;
}

void DifferentialSpec::set_efficiency(double value) {
    if (efficiency == value) {
        return;
    }
    efficiency = value;
    emit_changed();
}

double DifferentialSpec::get_efficiency() const {
    return efficiency;
}

void DifferentialSpec::set_locking_strength(double value) {
    if (locking_strength == value) {
        return;
    }
    locking_strength = value;
    emit_changed();
}

double DifferentialSpec::get_locking_strength() const {
    return locking_strength;
}

} // namespace godot
