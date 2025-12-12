#pragma once

#include "godot_cpp/classes/resource.hpp"
#include "godot_cpp/classes/wrapped.hpp"
#include "godot_cpp/variant/variant.hpp"

using namespace godot;

class MoVeEngine : public Resource {
private:
    GDCLASS(MoVeEngine, Resource);
//properties
    //engine
    double m_bore;          // mm
    double m_stroke;        // mm
    int m_cylinders;        // number
    double m_peak_rpm_base;   // rpm
    double m_sigma_left;      // arbitrary
    double m_sigma_right;     // arbitrary
    double m_idle_rpm;
    double m_redline_rpm; // nvm
    double m_brake_base;       // Nm of braking at idle RPM
    double m_brake_exp; 
    double m_friction_coeff; // Nm per 1000 rpm 
    double m_inertia = 0.15f;
    //turbo
    double m_wastegate_bar;   // max boost in bar
    double m_spool_rpm;        // rpm, turbo reaches efficiency island
    double m_spool_k;         // arbitrary
    // rev limiter (bouncy / 2-step)
    double rev_limit_rpm = 7000.0f;
    double rev_soft_zone = 150.0f;
    bool limiter_active = false;
    double limiter_timer = 0.0f;
    double limiter_cycle_period = 0.08f; // seconds
    double limiter_cut_ratio = 0.5f; // fraction of cycle spent cutting
//const
    static constexpr double k_nm_per_liter = 120.0f; // newton meters per liter constant
//members
    double m_throttle;
    double m_current_rpm;
private:
    double displacement_liters() const;
    double get_load_torque(double in_rpm) const ;
protected:
    static void _bind_methods();
public:
    MoVeEngine();

    double engine_torque(double rpm);
    void update_rpm(double delta);

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

    // Idle / Braking
    void set_idle_rpm(double v); double get_idle_rpm() const;
    void set_brake_base(double v); double get_brake_base() const;
    void set_brake_exp(double v); double get_brake_exp() const;

    // Redline + Throttle
    void set_redline_rpm(double v); double get_redline_rpm() const;
    void set_throttle(double v); double get_throttle() const;

    //misc
    void set_friction_coeff(double v); double get_friction_coeff() const;
    void set_current_rpm(double v); double get_current_rpm() const;
};