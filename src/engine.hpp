#pragma once

#include "godot_cpp/classes/resource.hpp"
#include "godot_cpp/classes/wrapped.hpp"
#include "godot_cpp/variant/variant.hpp"

using namespace godot;

class MoVeEngine : public Resource {
private:
    GDCLASS(MoVeEngine, Resource);
//properties
    double m_bore;          // mm
    double m_stroke;        // mm
    int m_cylinders;        // number
    double peak_rpm_base;   // rpm
    double sigma_left;      // arbitrary
    double sigma_right;     // arbitrary
    double wastegate_bar;   // max boost in bar
    double spool_rpm        // rpm, turbo reaches efficiency island
    double spool_k;         // arbitrary
//const
    static const double k_nm_per_liter = 120.0f; // newton meters per liter constant
//members
    double rpm;
protected:
    static void _bind_methods();
public:
    MoVeEngine();

    double engine_torque(double throttle);
	void set_aero_down_force(double value);
	double get_aero_down_force() const;
};
