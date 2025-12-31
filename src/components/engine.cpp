#include "engine.hpp"

//#include "godot_cpp/variant/utility_functions.hpp"

using namespace godot;

double MoVeEngine::displacement_liters() const {
    double displacement_mm3 = (Math_PI / 4.0) * m_bore * m_bore * m_stroke * m_cylinders;
    double displacement_l = displacement_mm3 / 1e6;
    return displacement_l;
}

double MoVeEngine::get_load_torque(double rpm) const {
    // simple speed-proportional load
    return 5.0 + m_friction_coeff * (rpm / 1000.0); // base + friction
}

double MoVeEngine::engine_torque(double rpm) {
    // displacement in liters
    double displacement_l = MoVeEngine::displacement_liters();

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

    return torque_output; // Nm
}

void MoVeEngine::update_rpm(double delta) {
    // get torque values
    double torque = engine_torque(m_current_rpm);
    double torque_load = get_load_torque(m_current_rpm);
    double torque_net = torque - torque_load - m_reflected_load - m_drivetrain_torque;

    if (m_throttle < 0.02) {
        double rpm_error = m_idle_rpm - m_current_rpm;
        if (rpm_error > 0.0) {
            double idle_torque =
                Math::clamp(rpm_error * m_idle_kp, 0.0, m_idle_max_torque);
            torque_net += idle_torque;
        }
    }

    // alpha = torque_net / I ; omega_new = omega + alpha*delta
    double omega = m_current_rpm * (Math_TAU / 60.0f); // "60.0" converts rads to rpm
    double alpha = torque_net / m_inertia;
    omega += alpha * delta;
    
    if (omega < 0.0f) omega = 0.0f;
    m_current_rpm = omega * (60.0 / Math_TAU); // "60.0" converts rads to rpm

    m_current_rpm = Math::min(m_current_rpm, m_redline_rpm); // no idle clamp
    //m_current_rpm = Math::clamp(m_current_rpm, m_idle_rpm, m_redline_rpm);
}


void MoVeEngine::set_drivetrain_torque(double t) { m_drivetrain_torque = t; }
double MoVeEngine::get_drivetrain_torque() const { return m_drivetrain_torque; }

void MoVeEngine::set_reflected_load(double v) { m_reflected_load = v; }

void MoVeEngine::set_bore(double v) { m_bore = v; }
double MoVeEngine::get_bore() const { return m_bore; }

void MoVeEngine::set_stroke(double v) { m_stroke = v; }
double MoVeEngine::get_stroke() const { return m_stroke; }

void MoVeEngine::set_cylinders(int v) { m_cylinders = v; }
int MoVeEngine::get_cylinders() const { return m_cylinders; }

void MoVeEngine::set_peak_rpm_base(double v) { m_peak_rpm_base = v; }
double MoVeEngine::get_peak_rpm_base() const { return m_peak_rpm_base; }

void MoVeEngine::set_sigma_left(double v) { m_sigma_left = v; }
double MoVeEngine::get_sigma_left() const { return m_sigma_left; }

void MoVeEngine::set_sigma_right(double v) { m_sigma_right = v; }
double MoVeEngine::get_sigma_right() const { return m_sigma_right; }

void MoVeEngine::set_idle_rpm(double v) { m_idle_rpm = v; }
double MoVeEngine::get_idle_rpm() const { return m_idle_rpm; }

void MoVeEngine::set_redline_rpm(double v) { m_redline_rpm = v; }
double MoVeEngine::get_redline_rpm() const { return m_redline_rpm; }

void MoVeEngine::set_wastegate_bar(double v) { m_wastegate_bar = v; }
double MoVeEngine::get_wastegate_bar() const { return m_wastegate_bar; }

void MoVeEngine::set_spool_rpm(double v) { m_spool_rpm = v; }
double MoVeEngine::get_spool_rpm() const { return m_spool_rpm; }

void MoVeEngine::set_spool_k(double v) { m_spool_k = v; }
double MoVeEngine::get_spool_k() const { return m_spool_k; }

void MoVeEngine::set_throttle(double v) { m_throttle = fmax(0.0, fmin(v, 1.0)); }
double MoVeEngine::get_throttle() const { return m_throttle; }

void MoVeEngine::set_friction_coeff(double v) { m_friction_coeff = v; }
double MoVeEngine::get_friction_coeff() const { return m_friction_coeff; }

void MoVeEngine::set_current_rpm(double v) { m_current_rpm = v; }
double MoVeEngine::get_current_rpm() const { return m_current_rpm; }

void MoVeEngine::_bind_methods() {
    // Methods
    ClassDB::bind_method(D_METHOD("engine_torque", "rpm"), &MoVeEngine::engine_torque);
    ClassDB::bind_method(D_METHOD("update_rpm","delta"), &MoVeEngine::update_rpm);

    // Editable members
    ClassDB::bind_method(D_METHOD("set_throttle", "value"), &MoVeEngine::set_throttle);
    ClassDB::bind_method(D_METHOD("get_throttle"), &MoVeEngine::get_throttle);

    // Parameters
    ClassDB::bind_method(D_METHOD("set_bore", "value"), &MoVeEngine::set_bore);
    ClassDB::bind_method(D_METHOD("get_bore"), &MoVeEngine::get_bore);
    ClassDB::bind_method(D_METHOD("set_stroke", "value"), &MoVeEngine::set_stroke);
    ClassDB::bind_method(D_METHOD("get_stroke"), &MoVeEngine::get_stroke);
    ClassDB::bind_method(D_METHOD("set_cylinders", "value"), &MoVeEngine::set_cylinders);
    ClassDB::bind_method(D_METHOD("get_cylinders"), &MoVeEngine::get_cylinders);

    ADD_GROUP("Size", "");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "bore", PROPERTY_HINT_RANGE, "0,200,0.01"), "set_bore", "get_bore");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "stroke", PROPERTY_HINT_RANGE, "0,200,0.01"), "set_stroke", "get_stroke");
    ADD_PROPERTY(PropertyInfo(Variant::INT,   "cylinders", PROPERTY_HINT_RANGE, "1,16,1"), "set_cylinders", "get_cylinders");

    ClassDB::bind_method(D_METHOD("set_peak_rpm_base", "value"), &MoVeEngine::set_peak_rpm_base);
    ClassDB::bind_method(D_METHOD("get_peak_rpm_base"), &MoVeEngine::get_peak_rpm_base);
    ClassDB::bind_method(D_METHOD("set_sigma_left", "value"), &MoVeEngine::set_sigma_left);
    ClassDB::bind_method(D_METHOD("get_sigma_left"), &MoVeEngine::get_sigma_left);
    ClassDB::bind_method(D_METHOD("set_sigma_right", "value"), &MoVeEngine::set_sigma_right);
    ClassDB::bind_method(D_METHOD("get_sigma_right"), &MoVeEngine::get_sigma_right);

    ADD_GROUP("Torque Curve", "");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "peak_rpm_base", PROPERTY_HINT_RANGE, "500,12000,1"), "set_peak_rpm_base", "get_peak_rpm_base");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "sigma_left", PROPERTY_HINT_RANGE, "0,3000,1"), "set_sigma_left", "get_sigma_left");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "sigma_right", PROPERTY_HINT_RANGE, "0,3000,1"), "set_sigma_right", "get_sigma_right");

    ClassDB::bind_method(D_METHOD("set_wastegate_bar", "value"), &MoVeEngine::set_wastegate_bar);
    ClassDB::bind_method(D_METHOD("get_wastegate_bar"), &MoVeEngine::get_wastegate_bar);
    ClassDB::bind_method(D_METHOD("set_spool_rpm", "value"), &MoVeEngine::set_spool_rpm);
    ClassDB::bind_method(D_METHOD("get_spool_rpm"), &MoVeEngine::get_spool_rpm);
    ClassDB::bind_method(D_METHOD("set_spool_k", "value"), &MoVeEngine::set_spool_k);
    ClassDB::bind_method(D_METHOD("get_spool_k"), &MoVeEngine::get_spool_k);

    ADD_GROUP("Turbo", "");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "wastegate_bar", PROPERTY_HINT_RANGE, "0,3,0.01"), "set_wastegate_bar", "get_wastegate_bar");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "spool_rpm", PROPERTY_HINT_RANGE, "0,20000,1"), "set_spool_rpm", "get_spool_rpm");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "spool_k", PROPERTY_HINT_RANGE, "0,2000,1"), "set_spool_k", "get_spool_k");

    ClassDB::bind_method(D_METHOD("set_idle_rpm", "value"), &MoVeEngine::set_idle_rpm);
    ClassDB::bind_method(D_METHOD("get_idle_rpm"), &MoVeEngine::get_idle_rpm);
    ClassDB::bind_method(D_METHOD("set_redline_rpm", "value"), &MoVeEngine::set_redline_rpm);
    ClassDB::bind_method(D_METHOD("get_redline_rpm"), &MoVeEngine::get_redline_rpm);

    ADD_GROUP("Idle & Redline", "");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "idle_rpm", PROPERTY_HINT_RANGE, "300,3000,1"), "set_idle_rpm", "get_idle_rpm");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "redline_rpm", PROPERTY_HINT_RANGE, "1000,20000,1"), "set_redline_rpm", "get_redline_rpm");

    ClassDB::bind_method(D_METHOD("set_friction_coeff", "value"), &MoVeEngine::set_friction_coeff);
    ClassDB::bind_method(D_METHOD("get_friction_coeff"), &MoVeEngine::get_friction_coeff);
    ClassDB::bind_method(D_METHOD("set_current_rpm", "value"), &MoVeEngine::set_current_rpm);
    ClassDB::bind_method(D_METHOD("get_current_rpm"), &MoVeEngine::get_current_rpm);

    ADD_GROUP("Misc", "");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "friction_coeff", PROPERTY_HINT_RANGE, "0,50,0.1"), "set_friction_coeff", "get_friction_coeff");
}