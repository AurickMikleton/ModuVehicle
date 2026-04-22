#include "engine.hpp"

using namespace godot;

double GasEngine::displacement_liters() const {
	double displacement_mm3 = (Math_PI / 4.0) * m_bore * m_bore * m_stroke * m_cylinders;
	double displacement_l = displacement_mm3 / 1e6;
	return displacement_l;
}

double GasEngine::get_load_torque(double rpm) const {
	// simple speed-proportional load
	return 5.0 + m_friction_coeff * (rpm / 1000.0); // base + friction
}

double GasEngine::engine_torque(double rpm) {
	double displacement_liters = GasEngine::displacement_liters();

	// naturally aspirated peak torque
	double torque_peak = k_nm_per_liter * displacement_liters;

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
	double a = 0.30; // linear part
	double p = 1.0 + 2.0 * (rpm / m_redline_rpm);
	double throttle_factor = a * m_throttle + (1.0 - a) * pow(m_throttle, p);

	double torque_output = torque_turbo_full * throttle_factor;

	return torque_output; // Nm
}

void GasEngine::update_rpm(double delta) {
	double engine_net_torque = engine_torque(m_current_rpm) - m_reflected_load;

	// Closed-throttle engine drag
	if (m_throttle < 0.02) {
		engine_net_torque -= 20.0 + 0.02 * m_current_rpm; // tune
	}

	double engine_alpha = engine_net_torque / Math::max(m_inertia, 0.001);
	double engine_omega = m_current_rpm * (Math_TAU / 60.0); // "60.0" converts rpm to rads
	//
	engine_omega += engine_alpha * delta;

	double idle_omega = m_idle_rpm * (Math_TAU / 60.0);
	engine_omega = Math::max(engine_omega, idle_omega);
	m_current_rpm = (engine_omega * (60.0 / Math_TAU));
}

void GasEngine::set_reflected_load(double v) { m_reflected_load = v; }

void GasEngine::set_bore(double v) { m_bore = v; }
double GasEngine::get_bore() const { return m_bore; }

void GasEngine::set_stroke(double v) { m_stroke = v; }
double GasEngine::get_stroke() const { return m_stroke; }

void GasEngine::set_cylinders(int v) { m_cylinders = v; }
int GasEngine::get_cylinders() const { return m_cylinders; }

void GasEngine::set_peak_rpm_base(double v) { m_peak_rpm_base = v; }
double GasEngine::get_peak_rpm_base() const { return m_peak_rpm_base; }

void GasEngine::set_sigma_left(double v) { m_sigma_left = v; }
double GasEngine::get_sigma_left() const { return m_sigma_left; }

void GasEngine::set_sigma_right(double v) { m_sigma_right = v; }
double GasEngine::get_sigma_right() const { return m_sigma_right; }

void GasEngine::set_idle_rpm(double v) { m_idle_rpm = v; }
double GasEngine::get_idle_rpm() const { return m_idle_rpm; }

void GasEngine::set_redline_rpm(double v) { m_redline_rpm = v; }
double GasEngine::get_redline_rpm() const { return m_redline_rpm; }

void GasEngine::set_wastegate_bar(double v) { m_wastegate_bar = v; }
double GasEngine::get_wastegate_bar() const { return m_wastegate_bar; }

void GasEngine::set_spool_rpm(double v) { m_spool_rpm = v; }
double GasEngine::get_spool_rpm() const { return m_spool_rpm; }

void GasEngine::set_spool_k(double v) { m_spool_k = v; }
double GasEngine::get_spool_k() const { return m_spool_k; }

void GasEngine::set_throttle(double v) { m_throttle = fmax(0.0, fmin(v, 1.0)); }
double GasEngine::get_throttle() const { return m_throttle; }

void GasEngine::set_friction_coeff(double v) { m_friction_coeff = v; }
double GasEngine::get_friction_coeff() const { return m_friction_coeff; }

void GasEngine::set_current_rpm(double v) { m_current_rpm = v; }
double GasEngine::get_current_rpm() const { return m_current_rpm; }

void GasEngine::_bind_methods() {
	// Methods
	ClassDB::bind_method(D_METHOD("engine_torque", "rpm"), &GasEngine::engine_torque);
	ClassDB::bind_method(D_METHOD("update_rpm", "delta"), &GasEngine::update_rpm);

	// Editable members
	ClassDB::bind_method(D_METHOD("set_throttle", "value"), &GasEngine::set_throttle);
	ClassDB::bind_method(D_METHOD("get_throttle"), &GasEngine::get_throttle);

	// Parameters
	ClassDB::bind_method(D_METHOD("set_bore", "value"), &GasEngine::set_bore);
	ClassDB::bind_method(D_METHOD("get_bore"), &GasEngine::get_bore);
	ClassDB::bind_method(D_METHOD("set_stroke", "value"), &GasEngine::set_stroke);
	ClassDB::bind_method(D_METHOD("get_stroke"), &GasEngine::get_stroke);
	ClassDB::bind_method(D_METHOD("set_cylinders", "value"), &GasEngine::set_cylinders);
	ClassDB::bind_method(D_METHOD("get_cylinders"), &GasEngine::get_cylinders);

	ADD_GROUP("Size", "");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "bore", PROPERTY_HINT_RANGE, "0,200,0.01"), "set_bore", "get_bore");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "stroke", PROPERTY_HINT_RANGE, "0,200,0.01"), "set_stroke", "get_stroke");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "cylinders", PROPERTY_HINT_RANGE, "1,16,1"), "set_cylinders", "get_cylinders");

	ClassDB::bind_method(D_METHOD("set_peak_rpm_base", "value"), &GasEngine::set_peak_rpm_base);
	ClassDB::bind_method(D_METHOD("get_peak_rpm_base"), &GasEngine::get_peak_rpm_base);
	ClassDB::bind_method(D_METHOD("set_sigma_left", "value"), &GasEngine::set_sigma_left);
	ClassDB::bind_method(D_METHOD("get_sigma_left"), &GasEngine::get_sigma_left);
	ClassDB::bind_method(D_METHOD("set_sigma_right", "value"), &GasEngine::set_sigma_right);
	ClassDB::bind_method(D_METHOD("get_sigma_right"), &GasEngine::get_sigma_right);

	ADD_GROUP("Torque Curve", "");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "peak_rpm_base", PROPERTY_HINT_RANGE, "500,12000,1"), "set_peak_rpm_base", "get_peak_rpm_base");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "sigma_left", PROPERTY_HINT_RANGE, "0,3000,1"), "set_sigma_left", "get_sigma_left");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "sigma_right", PROPERTY_HINT_RANGE, "0,3000,1"), "set_sigma_right", "get_sigma_right");

	ClassDB::bind_method(D_METHOD("set_wastegate_bar", "value"), &GasEngine::set_wastegate_bar);
	ClassDB::bind_method(D_METHOD("get_wastegate_bar"), &GasEngine::get_wastegate_bar);
	ClassDB::bind_method(D_METHOD("set_spool_rpm", "value"), &GasEngine::set_spool_rpm);
	ClassDB::bind_method(D_METHOD("get_spool_rpm"), &GasEngine::get_spool_rpm);
	ClassDB::bind_method(D_METHOD("set_spool_k", "value"), &GasEngine::set_spool_k);
	ClassDB::bind_method(D_METHOD("get_spool_k"), &GasEngine::get_spool_k);

	ADD_GROUP("Turbo", "");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "wastegate_bar", PROPERTY_HINT_RANGE, "0,3,0.01"), "set_wastegate_bar", "get_wastegate_bar");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "spool_rpm", PROPERTY_HINT_RANGE, "0,20000,1"), "set_spool_rpm", "get_spool_rpm");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "spool_k", PROPERTY_HINT_RANGE, "0,2000,1"), "set_spool_k", "get_spool_k");

	ClassDB::bind_method(D_METHOD("set_idle_rpm", "value"), &GasEngine::set_idle_rpm);
	ClassDB::bind_method(D_METHOD("get_idle_rpm"), &GasEngine::get_idle_rpm);
	ClassDB::bind_method(D_METHOD("set_redline_rpm", "value"), &GasEngine::set_redline_rpm);
	ClassDB::bind_method(D_METHOD("get_redline_rpm"), &GasEngine::get_redline_rpm);

	ADD_GROUP("Idle & Redline", "");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "idle_rpm", PROPERTY_HINT_RANGE, "300,3000,1"), "set_idle_rpm", "get_idle_rpm");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "redline_rpm", PROPERTY_HINT_RANGE, "1000,20000,1"), "set_redline_rpm", "get_redline_rpm");

	ClassDB::bind_method(D_METHOD("set_friction_coeff", "value"), &GasEngine::set_friction_coeff);
	ClassDB::bind_method(D_METHOD("get_friction_coeff"), &GasEngine::get_friction_coeff);
	ClassDB::bind_method(D_METHOD("set_current_rpm", "value"), &GasEngine::set_current_rpm);
	ClassDB::bind_method(D_METHOD("get_current_rpm"), &GasEngine::get_current_rpm);

	ADD_GROUP("Misc", "");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "friction_coeff", PROPERTY_HINT_RANGE, "0,50,0.1"), "set_friction_coeff", "get_friction_coeff");
}
