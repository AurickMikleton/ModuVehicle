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

class AeroSpec : public Resource {
    GDCLASS(AeroSpec, Resource)

private:
    String display_name = "Road-car aero";
    double drag_coefficient = 0.34;
    double frontal_area_m2 = 2.15;
    double downforce_coefficient = 0.12;
    double downforce_front_share = 0.48;

protected:
    static void _bind_methods();

public:
    AeroSpec();

    void set_display_name(const String &value);
    String get_display_name() const;

    void set_drag_coefficient(double value);
    double get_drag_coefficient() const;

    void set_frontal_area_m2(double value);
    double get_frontal_area_m2() const;

    void set_downforce_coefficient(double value);
    double get_downforce_coefficient() const;

    void set_downforce_front_share(double value);
    double get_downforce_front_share() const;

};

} // namespace godot
