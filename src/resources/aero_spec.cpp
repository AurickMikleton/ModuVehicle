#include "aero_spec.hpp"

namespace godot {

AeroSpec::AeroSpec() {
}

void AeroSpec::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_display_name", "value"), &AeroSpec::set_display_name);
    ClassDB::bind_method(D_METHOD("get_display_name"), &AeroSpec::get_display_name);
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "display_name"),
        "set_display_name", "get_display_name");

    ClassDB::bind_method(D_METHOD("set_drag_coefficient", "value"), &AeroSpec::set_drag_coefficient);
    ClassDB::bind_method(D_METHOD("get_drag_coefficient"), &AeroSpec::get_drag_coefficient);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "drag_coefficient", PROPERTY_HINT_RANGE, "0.0,2.0,0.01"),
        "set_drag_coefficient", "get_drag_coefficient");

    ClassDB::bind_method(D_METHOD("set_frontal_area_m2", "value"), &AeroSpec::set_frontal_area_m2);
    ClassDB::bind_method(D_METHOD("get_frontal_area_m2"), &AeroSpec::get_frontal_area_m2);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "frontal_area_m2", PROPERTY_HINT_RANGE, "0.0,5.0,0.01"),
        "set_frontal_area_m2", "get_frontal_area_m2");

    ClassDB::bind_method(D_METHOD("set_downforce_coefficient", "value"), &AeroSpec::set_downforce_coefficient);
    ClassDB::bind_method(D_METHOD("get_downforce_coefficient"), &AeroSpec::get_downforce_coefficient);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "downforce_coefficient", PROPERTY_HINT_RANGE, "0.0,5.0,0.01"),
        "set_downforce_coefficient", "get_downforce_coefficient");

    ClassDB::bind_method(D_METHOD("set_downforce_front_share", "value"), &AeroSpec::set_downforce_front_share);
    ClassDB::bind_method(D_METHOD("get_downforce_front_share"), &AeroSpec::get_downforce_front_share);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "downforce_front_share", PROPERTY_HINT_RANGE, "0.0,1.0,0.01"),
        "set_downforce_front_share", "get_downforce_front_share");

}

void AeroSpec::set_display_name(const String &value) {
    if (display_name == value) {
        return;
    }
    display_name = value;
    emit_changed();
}

String AeroSpec::get_display_name() const {
    return display_name;
}

void AeroSpec::set_drag_coefficient(double value) {
    if (drag_coefficient == value) {
        return;
    }
    drag_coefficient = value;
    emit_changed();
}

double AeroSpec::get_drag_coefficient() const {
    return drag_coefficient;
}

void AeroSpec::set_frontal_area_m2(double value) {
    if (frontal_area_m2 == value) {
        return;
    }
    frontal_area_m2 = value;
    emit_changed();
}

double AeroSpec::get_frontal_area_m2() const {
    return frontal_area_m2;
}

void AeroSpec::set_downforce_coefficient(double value) {
    if (downforce_coefficient == value) {
        return;
    }
    downforce_coefficient = value;
    emit_changed();
}

double AeroSpec::get_downforce_coefficient() const {
    return downforce_coefficient;
}

void AeroSpec::set_downforce_front_share(double value) {
    if (downforce_front_share == value) {
        return;
    }
    downforce_front_share = value;
    emit_changed();
}

double AeroSpec::get_downforce_front_share() const {
    return downforce_front_share;
}

} // namespace godot
