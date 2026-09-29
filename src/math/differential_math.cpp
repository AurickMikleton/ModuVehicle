#include "differential_math.hpp"

[[nodiscard]] double wheel_torque(
	double total_torque,
	double wheel_weight,
	double total_weight,
	double wheel_omega,
	double average_omega,
	const godot::DifferentialSpec &spec
) {
	if (wheel_weight <= 0.0 || total_weight <= 0.0) return 0.0;
	const double nominal {total_torque * wheel_weight / total_weight};
	const double transfer_capacity {std::abs(total_torque) * spec.locking_strength * 0.25};
	const double correction {std::clamp(
		(average_omega - wheel_omega) * spec.locking_strength * 16.0,
		-transfer_capacity,
		transfer_capacity
	)};
	return nominal + correction;
}

