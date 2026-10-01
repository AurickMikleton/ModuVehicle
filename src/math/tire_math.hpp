#include <godot_cpp/variant/vector2.hpp>

#include "resources/tire_spec.hpp"
#include "resources/assist_spec.hpp"

#include <cmath>

struct WheelIntegrationResult {
	double omega;
	godot::Vector2 force;
};

[[nodiscard]] constexpr double sign (double value) {
	return static_cast<double>((0.0 < value) - (value < 0.0));
}

[[nodiscard]] godot::Vector2 combined_force(double slip_ratio, double slip_angle, double normal_load, const godot::TireSpec &tire);
[[nodiscard]] double slip_ratio(double wheel_surface_speed, double ground_speed);
[[nodiscard]] double slip_angle(double longitudinal_speed, double lateral_speed);
[[nodiscard]] double rolling_resistance_torque(double normal_load, double radius, const godot::TireSpec &tire);

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
);
