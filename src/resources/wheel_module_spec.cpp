#include "wheel_module_spec.hpp"

namespace godot {

WheelModuleSpec::WheelModuleSpec() {
}

void WheelModuleSpec::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_display_name", "value"), &WheelModuleSpec::set_display_name);
    ClassDB::bind_method(D_METHOD("get_display_name"), &WheelModuleSpec::get_display_name);
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "display_name"),
        "set_display_name", "get_display_name");

    ClassDB::bind_method(D_METHOD("set_mount_position", "value"), &WheelModuleSpec::set_mount_position);
    ClassDB::bind_method(D_METHOD("get_mount_position"), &WheelModuleSpec::get_mount_position);
    ADD_PROPERTY(PropertyInfo(Variant::VECTOR3, "mount_position"),
        "set_mount_position", "get_mount_position");

    ClassDB::bind_method(D_METHOD("set_radius", "value"), &WheelModuleSpec::set_radius);
    ClassDB::bind_method(D_METHOD("get_radius"), &WheelModuleSpec::get_radius);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "radius", PROPERTY_HINT_RANGE, "0.1,1.2,0.01"),
        "set_radius", "get_radius");

    ClassDB::bind_method(D_METHOD("set_width", "value"), &WheelModuleSpec::set_width);
    ClassDB::bind_method(D_METHOD("get_width"), &WheelModuleSpec::get_width);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "width", PROPERTY_HINT_RANGE, "0.05,0.8,0.01"),
        "set_width", "get_width");

    ClassDB::bind_method(D_METHOD("set_rotational_inertia", "value"), &WheelModuleSpec::set_rotational_inertia);
    ClassDB::bind_method(D_METHOD("get_rotational_inertia"), &WheelModuleSpec::get_rotational_inertia);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "rotational_inertia", PROPERTY_HINT_RANGE, "0.1,10.0,0.01"),
        "set_rotational_inertia", "get_rotational_inertia");

    ClassDB::bind_method(D_METHOD("set_steering_ratio", "value"), &WheelModuleSpec::set_steering_ratio);
    ClassDB::bind_method(D_METHOD("get_steering_ratio"), &WheelModuleSpec::get_steering_ratio);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "steering_ratio", PROPERTY_HINT_RANGE, "-1.0,1.0,0.01"),
        "set_steering_ratio", "get_steering_ratio");

    ClassDB::bind_method(D_METHOD("set_drive_weight", "value"), &WheelModuleSpec::set_drive_weight);
    ClassDB::bind_method(D_METHOD("get_drive_weight"), &WheelModuleSpec::get_drive_weight);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "drive_weight", PROPERTY_HINT_RANGE, "0.0,1.0,0.01"),
        "set_drive_weight", "get_drive_weight");

    ClassDB::bind_method(D_METHOD("set_brake_weight", "value"), &WheelModuleSpec::set_brake_weight);
    ClassDB::bind_method(D_METHOD("get_brake_weight"), &WheelModuleSpec::get_brake_weight);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "brake_weight", PROPERTY_HINT_RANGE, "0.0,1.0,0.01"),
        "set_brake_weight", "get_brake_weight");

    ClassDB::bind_method(D_METHOD("set_handbrake_weight", "value"), &WheelModuleSpec::set_handbrake_weight);
    ClassDB::bind_method(D_METHOD("get_handbrake_weight"), &WheelModuleSpec::get_handbrake_weight);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "handbrake_weight", PROPERTY_HINT_RANGE, "0.0,1.0,0.01"),
        "set_handbrake_weight", "get_handbrake_weight");

    ClassDB::bind_method(D_METHOD("set_tire", "value"), &WheelModuleSpec::set_tire);
    ClassDB::bind_method(D_METHOD("get_tire"), &WheelModuleSpec::get_tire);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "tire", PROPERTY_HINT_RESOURCE_TYPE, "TireSpec"),
        "set_tire", "get_tire");

    ClassDB::bind_method(D_METHOD("set_suspension", "value"), &WheelModuleSpec::set_suspension);
    ClassDB::bind_method(D_METHOD("get_suspension"), &WheelModuleSpec::get_suspension);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "suspension", PROPERTY_HINT_RESOURCE_TYPE, "SuspensionSpec"),
        "set_suspension", "get_suspension");

}

void WheelModuleSpec::set_display_name(const String &value) {
    if (display_name == value) {
        return;
    }
    display_name = value;
    emit_changed();
}

String WheelModuleSpec::get_display_name() const {
    return display_name;
}

void WheelModuleSpec::set_mount_position(const Vector3 &value) {
    if (mount_position == value) {
        return;
    }
    mount_position = value;
    emit_changed();
}

Vector3 WheelModuleSpec::get_mount_position() const {
    return mount_position;
}

void WheelModuleSpec::set_radius(double value) {
    if (radius == value) {
        return;
    }
    radius = value;
    emit_changed();
}

double WheelModuleSpec::get_radius() const {
    return radius;
}

void WheelModuleSpec::set_width(double value) {
    if (width == value) {
        return;
    }
    width = value;
    emit_changed();
}

double WheelModuleSpec::get_width() const {
    return width;
}

void WheelModuleSpec::set_rotational_inertia(double value) {
    if (rotational_inertia == value) {
        return;
    }
    rotational_inertia = value;
    emit_changed();
}

double WheelModuleSpec::get_rotational_inertia() const {
    return rotational_inertia;
}

void WheelModuleSpec::set_steering_ratio(double value) {
    if (steering_ratio == value) {
        return;
    }
    steering_ratio = value;
    emit_changed();
}

double WheelModuleSpec::get_steering_ratio() const {
    return steering_ratio;
}

void WheelModuleSpec::set_drive_weight(double value) {
    if (drive_weight == value) {
        return;
    }
    drive_weight = value;
    emit_changed();
}

double WheelModuleSpec::get_drive_weight() const {
    return drive_weight;
}

void WheelModuleSpec::set_brake_weight(double value) {
    if (brake_weight == value) {
        return;
    }
    brake_weight = value;
    emit_changed();
}

double WheelModuleSpec::get_brake_weight() const {
    return brake_weight;
}

void WheelModuleSpec::set_handbrake_weight(double value) {
    if (handbrake_weight == value) {
        return;
    }
    handbrake_weight = value;
    emit_changed();
}

double WheelModuleSpec::get_handbrake_weight() const {
    return handbrake_weight;
}

void WheelModuleSpec::set_tire(const Ref<TireSpec> &value) {
    if (tire == value) {
        return;
    }
    tire = value;
    emit_changed();
}

Ref<TireSpec> WheelModuleSpec::get_tire() const {
    return tire;
}

void WheelModuleSpec::set_suspension(const Ref<SuspensionSpec> &value) {
    if (suspension == value) {
        return;
    }
    suspension = value;
    emit_changed();
}

Ref<SuspensionSpec> WheelModuleSpec::get_suspension() const {
    return suspension;
}

} // namespace godot
