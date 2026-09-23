#pragma once

#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/packed_float32_array.hpp>
#include <godot_cpp/variant/string.hpp>

#include <cstdint>

namespace godot {

class EngineSpec final : public Resource {
    GDCLASS(EngineSpec, Resource)

public:
    String display_name = "Engine";

    // Operating range
    double idle_rpm {850.0};
    double redline_rpm {7000.0};
    double rotational_inertia {0.30};
    double friction_nm {18.0};
    double engine_braking_nm {48.0};
    double engine_braking_exponent {1.4};

    // Torque curve
    // Describes NA engien
    PackedFloat32Array torque_samples;
    double peak_torque_nm {470.0};
    double torque_multiplier {1.0};

    // General forced induction
    bool turbocharged {true};
    double max_boost_bar {0.8};
    double boost_threshold_rpm {2500.0};

    // Supercharger
    // 0 = None, 1 = Roots, 2 = Centrifugal
    int64_t supercharger_type {0};
    double supercharger_max_boost_bar {0.6};
    // Boost fraction near idle
    double roots_low_rpm_boost_fraction {0.75};
    // Converts pressure ratio to torque gain
    double supercharger_charge_efficiency {0.8};
    // Belt-drive power demand at redline and full load
    double supercharger_drive_loss_kw {12.0};

protected:
    static void _bind_methods();

public:
    EngineSpec();

    void set_display_name(const String &value);
    String get_display_name() const;

    void set_idle_rpm(double value);
    double get_idle_rpm() const;

    void set_redline_rpm(double value);
    double get_redline_rpm() const;

    void set_rotational_inertia(double value);
    double get_rotational_inertia() const;

    void set_friction_nm(double value);
    double get_friction_nm() const;

    void set_engine_braking_nm(double value);
    double get_engine_braking_nm() const;

    void set_engine_braking_exponent(double value);
    double get_engine_braking_exponent() const;

    void set_torque_samples(const PackedFloat32Array &value);
    PackedFloat32Array get_torque_samples() const;

    void set_peak_torque_nm(double value);
    double get_peak_torque_nm() const;

    void set_torque_multiplier(double value);
    double get_torque_multiplier() const;

    void set_turbocharged(bool value);
    bool get_turbocharged() const;

    void set_max_boost_bar(double value);
    double get_max_boost_bar() const;

    void set_boost_threshold_rpm(double value);
    double get_boost_threshold_rpm() const;

    void set_supercharger_type(int64_t value);
    int64_t get_supercharger_type() const;

    void set_supercharger_max_boost_bar(double value);
    double get_supercharger_max_boost_bar() const;

    void set_roots_low_rpm_boost_fraction(double value);
    double get_roots_low_rpm_boost_fraction() const;

    void set_supercharger_charge_efficiency(double value);
    double get_supercharger_charge_efficiency() const;

    void set_supercharger_drive_loss_kw(double value);
    double get_supercharger_drive_loss_kw() const;
};

} // namespace godot
