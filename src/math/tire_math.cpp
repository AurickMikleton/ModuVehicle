#include "tire_math.hpp"

[[nodiscard]] godot::Vector2 combined_force(double slip_ratio, double slip_angle, double normal_load, const godot::TireSpec &tire) {
	if (normal_load <= 0.0) return godot::Vector2{};
	const double reference_load {3500.0};
	const double load_scale {std::pow(std::max(normal_load / reference_load, -1.05), tire.load_sensitivity)};
	const double limit {tire.friction_coefficient * normal_load};
	const double longitudinal_slope {tire.longitudinal_stiffness * load_scale};
	const double lateral_slope {tire.lateral_stiffness * load_scale};
	const double raw_long {std::tanh(slip_ratio * longitudinal_slope / std::max(limit, 1.0)) * limit};
	const double raw_lat {-std::tanh(slip_angle * lateral_slope / std::max(limit, 1.0)) * limit};
	const godot::Vector2 demand{static_cast<godot::real_t>(raw_long), static_cast<godot::real_t>(raw_lat)};
	return (demand.length() > limit)
		? demand.normalized() * limit
		: demand;
}

[[nodiscard]] double slip_ratio(double wheel_surface_speed, double ground_speed) {
	return (wheel_surface_speed - ground_speed) / std::max(std::abs(ground_speed), 2.0);
}

[[nodiscard]] double slip_angle(double longitudinal_speed, double lateral_speed) {
	return std::atan2(lateral_speed, std::abs(longitudinal_speed) + 0.5);
}

[[nodiscard]] double rolling_resistance_torque(double normal_load, double radius, const godot::TireSpec &tire) {
	return tire.rolling_resistance * normal_load * radius;
}

[[nodiscard]] WheelIntegrationResult integrate_wheel(
	double omega,
	double ground_speed,
	double angle,
	double normal_load,
	double radius,
	double inertia,
	double drive,
	double resistance,
	double delta,
	const godot::TireSpec &tire,
	const godot::AssistSpec &assists
) {
	const double dt {std::max(delta, 1e-6)};
	const double wheel_inertia {std::max(inertia, 1e-2)};
	double applied_drive {drive};
	if (assists.traction_control && std::abs(drive) > 1e-3) {
		const double direction {sign(drive)}; // Godot signf
		const double target {assists.target_drive_slip * direction};
		const double target_force {combined_force(target, angle, normal_load, tire).x};
		const double target_omega {(ground_speed + target * std::max(std::abs(ground_speed), 2.0)) / radius};
		const double torque_cap {std::max(
			0.0,
			direction * (target_force * radius + wheel_inertia * (target_omega - omega) / dt))
		};
		applied_drive = direction * std::min(std::abs(drive), torque_cap);
	}
	const auto zero_force{combined_force(slip_ratio(0.0, ground_speed), angle, normal_load, tire)};
    const double zero_residual{-omega - dt / wheel_inertia * (applied_drive - zero_force.x * radius)};
    const double brake_step{dt / wheel_inertia * resistance};
    double next_omega{0.0};
    if (std::abs(zero_residual) > brake_step) {
        const double bound{
            dt / wheel_inertia * (std::abs(applied_drive)
			+ tire.friction_coefficient * std::max(normal_load, 0.0) * radius
			+ resistance) + 1.0
        };
        double low{omega - bound};
        double high{omega + bound};

        for (int iteration{0}; iteration < 22; ++iteration) {
            const double middle{(low + high) * 0.5};
            const auto force{combined_force(slip_ratio(middle * radius, ground_speed), angle, normal_load, tire)};

            const double residual{
                middle - omega - dt / wheel_inertia * (
                    applied_drive
                    - force.x * radius
                    - sign(middle) * resistance
                )
            };

            if (residual > 0.0) {high = middle;}
			else {low = middle;}
        }

        next_omega = (low + high) * 0.5;
    }

    const auto result_force{combined_force(slip_ratio(next_omega * radius, ground_speed), angle, normal_load, tire)};

    return {next_omega, result_force};
 }

