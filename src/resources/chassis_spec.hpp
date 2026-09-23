#pragma once

#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/variant/string.hpp>
#include <godot_cpp/variant/vector3.hpp>
#include <godot_cpp/variant/packed_float32_array.hpp>
#include <godot_cpp/variant/typed_array.hpp>
#include <cstdint>

namespace godot {

class ChassisSpec : public Resource {
    GDCLASS(ChassisSpec, Resource)

private:
    String display_name = "Chassis";
    double mass_kg = 1450.0;
    Vector3 body_size = Vector3(static_cast<real_t>(1.85), static_cast<real_t>(0.55), static_cast<real_t>(4.25));
    Vector3 center_of_mass = Vector3(static_cast<real_t>(0.0), static_cast<real_t>(-0.38), static_cast<real_t>(0.10));
    // Optional artificial damping, replacing project/area damping. Normally zero:
    // Tire rolling resistance and AeroSpec already account for road resistance.
    double linear_damping = 0.0;
    double angular_damping = 0.55;

protected:
    static void _bind_methods();

public:
    ChassisSpec();

    void set_display_name(const String &value);
    String get_display_name() const;

    void set_mass_kg(double value);
    double get_mass_kg() const;

    void set_body_size(const Vector3 &value);
    Vector3 get_body_size() const;

    void set_center_of_mass(const Vector3 &value);
    Vector3 get_center_of_mass() const;

    void set_linear_damping(double value);
    double get_linear_damping() const;

    void set_angular_damping(double value);
    double get_angular_damping() const;

};

} // namespace godot
