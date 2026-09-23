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

class GearboxSpec : public Resource {
    GDCLASS(GearboxSpec, Resource)

private:
    String display_name = "6-speed";
    PackedFloat32Array forward_ratios;
    double reverse_ratio = 3.20;
    double efficiency = 0.90;
    bool automatic = true;
    double shift_duration = 0.22;
    double post_shift_hold = 0.45;
    double upshift_fraction = 0.88;
    double downshift_fraction = 0.30;

    // Clutch / converter
    double engage_rpm = 1400.0;
    double full_engagement_rpm = 2700.0;
    double clutch_capacity_nm = 620.0;
    double slip_gain = 8.0;

protected:
    static void _bind_methods();
    Variant _get_inspector_category() const;

public:
    GearboxSpec();

    void set_display_name(const String &value);
    String get_display_name() const;

    void set_forward_ratios(const PackedFloat32Array &value);
    PackedFloat32Array get_forward_ratios() const;

    void set_reverse_ratio(double value);
    double get_reverse_ratio() const;

    void set_efficiency(double value);
    double get_efficiency() const;

    void set_automatic(bool value);
    bool get_automatic() const;

    void set_shift_duration(double value);
    double get_shift_duration() const;

    void set_post_shift_hold(double value);
    double get_post_shift_hold() const;

    void set_upshift_fraction(double value);
    double get_upshift_fraction() const;

    void set_downshift_fraction(double value);
    double get_downshift_fraction() const;

    void set_engage_rpm(double value);
    double get_engage_rpm() const;

    void set_full_engagement_rpm(double value);
    double get_full_engagement_rpm() const;

    void set_clutch_capacity_nm(double value);
    double get_clutch_capacity_nm() const;

    void set_slip_gain(double value);
    double get_slip_gain() const;

};

} // namespace godot
