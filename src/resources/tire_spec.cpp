#include "tire_spec.hpp"

namespace godot {

TireSpec::TireSpec() {
}

void TireSpec::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_display_name", "value"), &TireSpec::set_display_name);
    ClassDB::bind_method(D_METHOD("get_display_name"), &TireSpec::get_display_name);
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "display_name"),
        "set_display_name", "get_display_name");

    ClassDB::bind_method(D_METHOD("set_friction_coefficient", "value"), &TireSpec::set_friction_coefficient);
    ClassDB::bind_method(D_METHOD("get_friction_coefficient"), &TireSpec::get_friction_coefficient);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "friction_coefficient", PROPERTY_HINT_RANGE, "0.1,2.0,0.01"),
        "set_friction_coefficient", "get_friction_coefficient");

    ClassDB::bind_method(D_METHOD("set_longitudinal_stiffness", "value"), &TireSpec::set_longitudinal_stiffness);
    ClassDB::bind_method(D_METHOD("get_longitudinal_stiffness"), &TireSpec::get_longitudinal_stiffness);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "longitudinal_stiffness", PROPERTY_HINT_RANGE, "100.0,150000.0,100.0"),
        "set_longitudinal_stiffness", "get_longitudinal_stiffness");

    ClassDB::bind_method(D_METHOD("set_lateral_stiffness", "value"), &TireSpec::set_lateral_stiffness);
    ClassDB::bind_method(D_METHOD("get_lateral_stiffness"), &TireSpec::get_lateral_stiffness);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "lateral_stiffness", PROPERTY_HINT_RANGE, "100.0,30000.0,100.0"),
        "set_lateral_stiffness", "get_lateral_stiffness");

    ClassDB::bind_method(D_METHOD("set_rolling_resistance", "value"), &TireSpec::set_rolling_resistance);
    ClassDB::bind_method(D_METHOD("get_rolling_resistance"), &TireSpec::get_rolling_resistance);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "rolling_resistance", PROPERTY_HINT_RANGE, "0.0,0.1,0.001"),
        "set_rolling_resistance", "get_rolling_resistance");

    ClassDB::bind_method(D_METHOD("set_load_sensitivity", "value"), &TireSpec::set_load_sensitivity);
    ClassDB::bind_method(D_METHOD("get_load_sensitivity"), &TireSpec::get_load_sensitivity);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "load_sensitivity", PROPERTY_HINT_RANGE, "0.1,2.0,0.01"),
        "set_load_sensitivity", "get_load_sensitivity");

}

void TireSpec::set_display_name(const String &value) {
    if (display_name == value) {
        return;
    }
    display_name = value;
    emit_changed();
}

String TireSpec::get_display_name() const {
    return display_name;
}

void TireSpec::set_friction_coefficient(double value) {
    if (friction_coefficient == value) {
        return;
    }
    friction_coefficient = value;
    emit_changed();
}

double TireSpec::get_friction_coefficient() const {
    return friction_coefficient;
}

void TireSpec::set_longitudinal_stiffness(double value) {
    if (longitudinal_stiffness == value) {
        return;
    }
    longitudinal_stiffness = value;
    emit_changed();
}

double TireSpec::get_longitudinal_stiffness() const {
    return longitudinal_stiffness;
}

void TireSpec::set_lateral_stiffness(double value) {
    if (lateral_stiffness == value) {
        return;
    }
    lateral_stiffness = value;
    emit_changed();
}

double TireSpec::get_lateral_stiffness() const {
    return lateral_stiffness;
}

void TireSpec::set_rolling_resistance(double value) {
    if (rolling_resistance == value) {
        return;
    }
    rolling_resistance = value;
    emit_changed();
}

double TireSpec::get_rolling_resistance() const {
    return rolling_resistance;
}

void TireSpec::set_load_sensitivity(double value) {
    if (load_sensitivity == value) {
        return;
    }
    load_sensitivity = value;
    emit_changed();
}

double TireSpec::get_load_sensitivity() const {
    return load_sensitivity;
}

} // namespace godot
