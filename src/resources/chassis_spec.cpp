#include "chassis_spec.hpp"

namespace godot {

ChassisSpec::ChassisSpec() {
}

void ChassisSpec::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_display_name", "value"), &ChassisSpec::set_display_name);
    ClassDB::bind_method(D_METHOD("get_display_name"), &ChassisSpec::get_display_name);
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "display_name"),
        "set_display_name", "get_display_name");

    ClassDB::bind_method(D_METHOD("set_mass_kg", "value"), &ChassisSpec::set_mass_kg);
    ClassDB::bind_method(D_METHOD("get_mass_kg"), &ChassisSpec::get_mass_kg);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "mass_kg", PROPERTY_HINT_RANGE, "20.0,10000.0,10.0"),
        "set_mass_kg", "get_mass_kg");

    ClassDB::bind_method(D_METHOD("set_body_size", "value"), &ChassisSpec::set_body_size);
    ClassDB::bind_method(D_METHOD("get_body_size"), &ChassisSpec::get_body_size);
    ADD_PROPERTY(PropertyInfo(Variant::VECTOR3, "body_size"),
        "set_body_size", "get_body_size");

    ClassDB::bind_method(D_METHOD("set_center_of_mass", "value"), &ChassisSpec::set_center_of_mass);
    ClassDB::bind_method(D_METHOD("get_center_of_mass"), &ChassisSpec::get_center_of_mass);
    ADD_PROPERTY(PropertyInfo(Variant::VECTOR3, "center_of_mass"),
        "set_center_of_mass", "get_center_of_mass");

    ClassDB::bind_method(D_METHOD("set_linear_damping", "value"), &ChassisSpec::set_linear_damping);
    ClassDB::bind_method(D_METHOD("get_linear_damping"), &ChassisSpec::get_linear_damping);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "linear_damping", PROPERTY_HINT_RANGE, "0.0,10.0,0.01"),
        "set_linear_damping", "get_linear_damping");

    ClassDB::bind_method(D_METHOD("set_angular_damping", "value"), &ChassisSpec::set_angular_damping);
    ClassDB::bind_method(D_METHOD("get_angular_damping"), &ChassisSpec::get_angular_damping);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "angular_damping", PROPERTY_HINT_RANGE, "0.0,10.0,0.01"),
        "set_angular_damping", "get_angular_damping");

}

void ChassisSpec::set_display_name(const String &value) {
    if (display_name == value) {
        return;
    }
    display_name = value;
    emit_changed();
}

String ChassisSpec::get_display_name() const {
    return display_name;
}

void ChassisSpec::set_mass_kg(double value) {
    if (mass_kg == value) {
        return;
    }
    mass_kg = value;
    emit_changed();
}

double ChassisSpec::get_mass_kg() const {
    return mass_kg;
}

void ChassisSpec::set_body_size(const Vector3 &value) {
    if (body_size == value) {
        return;
    }
    body_size = value;
    emit_changed();
}

Vector3 ChassisSpec::get_body_size() const {
    return body_size;
}

void ChassisSpec::set_center_of_mass(const Vector3 &value) {
    if (center_of_mass == value) {
        return;
    }
    center_of_mass = value;
    emit_changed();
}

Vector3 ChassisSpec::get_center_of_mass() const {
    return center_of_mass;
}

void ChassisSpec::set_linear_damping(double value) {
    if (linear_damping == value) {
        return;
    }
    linear_damping = value;
    emit_changed();
}

double ChassisSpec::get_linear_damping() const {
    return linear_damping;
}

void ChassisSpec::set_angular_damping(double value) {
    if (angular_damping == value) {
        return;
    }
    angular_damping = value;
    emit_changed();
}

double ChassisSpec::get_angular_damping() const {
    return angular_damping;
}

} // namespace godot
