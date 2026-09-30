#include "aero_math.hpp"

[[nodiscard]] godot::Vector3 drag_force(godot::Vector3 velocity, const godot::AeroSpec &spec) {
	const double speed {velocity.length()};
	if (speed < 1e-2) return godot::Vector3{};
	const double magnitude {
		0.5 * k_air_density
		* spec.downforce_coefficient
		* spec.frontal_area_m2
		* speed * speed
	};
	return -velocity.normalized() * magnitude;
}

[[nodiscard]] double downforce(double speed, const godot::AeroSpec &spec) {
	return 0.5 * k_air_density
		* spec.downforce_coefficient
		* spec.frontal_area_m2
		* speed * speed;
}

