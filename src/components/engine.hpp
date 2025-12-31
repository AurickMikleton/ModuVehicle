#pragma once

#include "godot_cpp/classes/resource.hpp"
#include "godot_cpp/classes/wrapped.hpp"
#include "godot_cpp/variant/variant.hpp"

#include "godot_cpp/variant/utility_functions.hpp"

using namespace godot;

class MoVeEngine : public Resource {
private:
    GDCLASS(MoVeEngine, Resource);
//properties
    //engine
    double m_bore = 99.5;           // mm
    double m_stroke = 79.0;         // mm
    int m_cylinders = 4;        // number
    double m_peak_rpm_base = 4200.0;    // rpm
    double m_sigma_left = 1200.0;      // arbitrary
    double m_sigma_right = 900.0;     // arbitrary
    double m_idle_rpm = 900.0;
    double m_redline_rpm = 7000.0; // nvm
    double m_friction_coeff = 8.0f; // Nm per 1000 rpm 
    double m_inertia = 0.15f;
    //turbo
    double m_wastegate_bar = 0.8;   // max boost in bar
    double m_spool_rpm = 2500.0;        // rpm, turbo reaches efficiency island
    double m_spool_k = 600.0;         // arbitrary
//const
    static constexpr double k_nm_per_liter = 120.0f; // newton meters per liter constant
//members
    double m_throttle = 1.0;
    double m_current_rpm = 900.0;
    double m_reflected_load = 0.0;
    double m_idle_kp = 0.4;    // proportional gain
    double m_idle_max_torque = 40.0; // Nm
    double m_drivetrain_torque = 0.0;
private:
    double displacement_liters() const;
    double get_load_torque(double in_rpm) const ;
protected:
    static void _bind_methods();
public:
    double engine_torque(double rpm);
    void update_rpm(double delta);

    void set_reflected_load(double v);

    void set_drivetrain_torque(double t);
    double get_drivetrain_torque() const;


    // Size
    void set_bore(double v); double get_bore() const;
    void set_stroke(double v); double get_stroke() const;
    void set_cylinders(int v); int get_cylinders() const;

    // Torque curve
    void set_peak_rpm_base(double v); double get_peak_rpm_base() const;
    void set_sigma_left(double v); double get_sigma_left() const;
    void set_sigma_right(double v); double get_sigma_right() const;

    // Turbo
    void set_wastegate_bar(double v); double get_wastegate_bar() const;
    void set_spool_rpm(double v); double get_spool_rpm() const;
    void set_spool_k(double v); double get_spool_k() const;

    // Idle + Redline + Throttle
    void set_idle_rpm(double v); double get_idle_rpm() const;
    void set_redline_rpm(double v); double get_redline_rpm() const;
    void set_throttle(double v); double get_throttle() const;

    //misc
    void set_friction_coeff(double v); double get_friction_coeff() const;
    void set_current_rpm(double v); double get_current_rpm() const;
};