#pragma once

#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/variant/string.hpp>
#include <godot_cpp/variant/vector3.hpp>
#include <godot_cpp/variant/packed_float32_array.hpp>
#include <godot_cpp/variant/typed_array.hpp>
#include <cstdint>
#include "suspension_spec.hpp"
#include "tire_spec.hpp"

namespace godot {

class WheelModuleSpec : public Resource {
    GDCLASS(WheelModuleSpec, Resource)

private:
    String display_name = "Wheel";
    Vector3 mount_position = Vector3();
    double radius = 0.34;
    double width = 0.24;
    double rotational_inertia = 1.25;
    double steering_ratio = 0.0;
    double drive_weight = 0.0;
    double brake_weight = 1.0;
    double handbrake_weight = 0.0;
    Ref<TireSpec> tire;
    Ref<SuspensionSpec> suspension;

protected:
    static void _bind_methods();

public:
    WheelModuleSpec();

    void set_display_name(const String &value);
    String get_display_name() const;

    void set_mount_position(const Vector3 &value);
    Vector3 get_mount_position() const;

    void set_radius(double value);
    double get_radius() const;

    void set_width(double value);
    double get_width() const;

    void set_rotational_inertia(double value);
    double get_rotational_inertia() const;

    void set_steering_ratio(double value);
    double get_steering_ratio() const;

    void set_drive_weight(double value);
    double get_drive_weight() const;

    void set_brake_weight(double value);
    double get_brake_weight() const;

    void set_handbrake_weight(double value);
    double get_handbrake_weight() const;

    void set_tire(const Ref<TireSpec> &value);
    Ref<TireSpec> get_tire() const;

    void set_suspension(const Ref<SuspensionSpec> &value);
    Ref<SuspensionSpec> get_suspension() const;

};

} // namespace godot
