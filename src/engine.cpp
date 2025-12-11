#include "engine.hpp"

using namespace godot;

double MoVeEngine::engine_torque(double rpm) {
    //throttle = fmax(0.0, fmin(throttle, 1.0)); // clamp throttle percentage, to be put elsewhere

    // displacement in liters
    const double pi = 3.14159265;
    double displacement_m3 = (pi / 4.0) * m_bore * m_bore * m_stroke * m_cylinders;
    double displacement_l = displacement_m3 * 1000.0;

    // naturally aspirated peak torque
    double torque_peak = k_nm_per_liter * displacement_l;

    // peak RPM, base on bore/stroke ratio
    double bore_stroke_ratio = m_bore / m_stroke;
    double rpm_peak = m_peak_rpm_base * bore_stroke_ratio;

    // asymmetric gaussian torque curve
    double sigma = (rpm <= rpm_peak ? m_sigma_left : m_sigma_right);
    double x = (rpm - rpm_peak) / sigma;
    double torque_NA_full = torque_peak * exp(-0.5 * x * x);

    // turbo spool proportion
    double spool = 1.0 / (1.0 + exp((m_spool_rpm - rpm) / m_spool_k));

    // boost pressure in bar
    double boost_bar = m_wastegate_bar * spool;

    // multiply volumetric efficiency for turbo torque
    double torque_turbo_full = torque_NA_full * (1.0f + boost_bar);

    // throttle
    double a = 0.30;  // linear part
    double p = 1.0 + 2.0 * (rpm / m_redline_rpm);
    double throttle_factor = a * m_throttle + (1.0 - a) * pow(m_throttle, p);

    double torque_output = torque_turbo_full * throttle_factor;

    // engine braking below 5% throttle
    if (m_throttle < 0.05f) {
        double braking_ratio = rpm / m_idle_rpm;
        float torque_brake = -m_brake_base * pow(braking_ratio, m_brake_exp);
        torque_output += torque_brake;
    }

    // set approx 0 to 0
    if (rpm < m_idle_rpm * 0.3f)
        torque_output = 0.0f;

    return torque_output;
}

MoVeEngine::MoVeEngine() {
    m_bore = 99.5;                 // mm
    m_stroke = 79.0;               // mm
    m_cylinders = 4;               // number
    m_peak_rpm_base = 4200.0;      // rpm
    m_sigma_left = 1200.0;         // arbitrary
    m_sigma_right = 900.0;         // arbitrary
    m_wastegate_bar = 0.8;         // max boost (0.8bar ~ 11.6psi)
    m_spool_rpm = 2500.0;          // rpm, turbo reaches efficiency island
    m_spool_k = 600.0;             // steepness of spool curve
    m_idle_rpm = 900.0;
    m_brake_base = 25.0;           // Nm of braking at idle RPM
    m_brake_exp = 1.4;             // braking curve exponent
    m_redline_rpm = 7000.0;
    m_throttle = 1.0;
}

void MoVeEngine::set_bore(double value) {m_bore = value;}
double MoVeEngine::get_bore() const {return m_bore;}

void MoVeEngine::set_stroke(double value) {m_stroke = value;}
double MoVeEngine::get_stroke() const {return m_stroke;}

void MoVeEngine::set_cylinders(int value) {m_cylinders = value;}
int MoVeEngine::get_cylinders() const {return m_cylinders;}


void MoVeEngine::_bind_methods() {
    ClassDB::bind_method(D_METHOD("engine_torque", "rpm"), &MoVeEngine::engine_torque);
    // setters getters
    ClassDB::bind_method(D_METHOD("set_bore"), &MoVeEngine::set_bore);
    ClassDB::bind_method(D_METHOD("get_bore"), &MoVeEngine::get_bore);
    ClassDB::bind_method(D_METHOD("set_stroke"), &MoVeEngine::set_stroke);
    ClassDB::bind_method(D_METHOD("get_stroke"), &MoVeEngine::get_stroke);
    ClassDB::bind_method(D_METHOD("set_cylinders"), &MoVeEngine::set_cylinders);
    ClassDB::bind_method(D_METHOD("get_cylinders"), &MoVeEngine::get_cylinders);

    ADD_GROUP("Size", "");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "bore", PROPERTY_HINT_RANGE, "0,120,0.01"), "set_bore", "get_bore");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "stroke", PROPERTY_HINT_RANGE, "0,120,0.01"), "set_stroke", "get_stroke");
    ADD_PROPERTY(PropertyInfo(Variant::INT, "cylinders", PROPERTY_HINT_RANGE, "0,16,1"), "set_cylinders", "get_cylinders");
}