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

class TireSpec : public Resource {
    GDCLASS(TireSpec, Resource)

private:
    String display_name = "Sport tire";
    double friction_coefficient = 1.08;
    // Force slope in N per unit slip at the reference load.
    double longitudinal_stiffness = 40000.0;
    double lateral_stiffness = 9500.0;
    double rolling_resistance = 0.015;
    double load_sensitivity = 0.92;

protected:
    static void _bind_methods();

public:
    TireSpec();

    void set_display_name(const String &value);
    String get_display_name() const;

    void set_friction_coefficient(double value);
    double get_friction_coefficient() const;

    void set_longitudinal_stiffness(double value);
    double get_longitudinal_stiffness() const;

    void set_lateral_stiffness(double value);
    double get_lateral_stiffness() const;

    void set_rolling_resistance(double value);
    double get_rolling_resistance() const;

    void set_load_sensitivity(double value);
    double get_load_sensitivity() const;

};

} // namespace godot
