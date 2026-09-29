#include "resources/differential_spec.hpp"

[[nodiscard]] double wheel_torque(
	double total_torque,
	double wheel_weight,
	double total_weight,
	double wheel_omega,
	double average_omega,
	const godot::DifferentialSpec &spec
);
