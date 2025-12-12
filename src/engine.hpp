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
    double m_redline_rpm;
    double m_brake_base;       // Nm of braking at idle RPM
    double m_brake_exp; 
    //turbo
    double m_wastegate_bar;   // max boost in bar
    double m_spool_rpm;        // rpm, turbo reaches efficiency island
    double m_spool_k;         // arbitrary
//const
    static constexpr double k_nm_per_liter = 120.0f; // newton meters per liter constant
//members
    double m_throttle;
protected:
    static void _bind_methods();
public:
    MoVeEngine();

    double engine_torque(double rpm);

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
};