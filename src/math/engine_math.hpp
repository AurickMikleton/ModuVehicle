#pragma once

#include <algorithm>

#include "../resources/engine_spec.hpp"
#include "curve_math.hpp"

[[nodiscard]] double gross_torque_nm(double rpm, double throttle, EngineSpec &spec) {
	const double rpm_t {godot::Math::inverse_lerp(
		spec.idle_rpm,
		spec.redline_rpm,
		std::clamp(rpm, spec.idle_rpm, spec.redline_rpm)
	)};
	double base {std::clamp(sample_uniform(spec.torque_samples, rpm_t), 0.0, 1.0)};
	base *= spec.peak_torque_nm * spec.torque_multiplier;
	double boost_multiplier {1.0};
	if (spec.turbocharged ) {
		const double boost_t {smoothstep(spec.boost_threshold_rpm, spec.redline_rpm * 0.78, rpm)}; // 0.78 is RPM % when under full boost
		boost_multiplier += spec.max_boost_bar * boost_t + std::clamp(throttle, 0.0, 1.0) * 0.42; // 0.42 is %age torque increase per bar of boost
	}
	const double limiter {(rpm >= spec.redline_rpm) ? 0.0 : 1.0};
	const double blower_boost {supercharger_boost_bar(rpm, throttle, spec)};
	boost_multiplier += blower_boost * spec.supercharger_charge_efficiency;
	return base * std::clamp(throttle, 0.0, 1.0) * boost_multiplier * limiter;
}

[[nodiscard]] double supercharger_boost_bar(double rpm, double throttle, EngineSpec &spec) {
	if (spec.supercharger_type == 0) return 0.0;
	const double speed {std::clamp(rpm / std::max(sec.redline_rpm, 1.0), 0.0, 1.2)}; // 1.2 limits speed to 120% of redline
	double power_w {spec.supercharger_drive_loss_kw * 1000.0 * speed * speed * speed};
	power_w *= std::lerp(0.08, 1.0, std::clamp(throttle, 0.0, 1.0)); // for 0.8 when throttle is closed 8% of WOT drag is applied
	return power_w / std::max(rpm * godot::Math::TAU / 60.0, 1.0); // 60 converts minutes to seconds
}

[[nodiscard]] double drag_torque_nm(double rpm, double throttle, EngineSpec spec);
[[nodiscard]] double idle_control_torque_nm(double rpm, EngineSpec spec);

