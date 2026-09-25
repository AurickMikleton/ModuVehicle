#include "suspension_math.hpp"

[[nodiscard]] SuspensionForceResult normal_force(double compression, double previous_compression, double delta, const godot::SuspensionSpec spec) {
	const double velocity {(compression - previous_compression) / std::max(delta, 1e-6)};
	const double damping {(velocity >= 0.0)
		? spec.compression_damping
		: spec.rebound_damping
	};
	const double force {std::max(compression * spec.spring_rate + velocity * damping, 0.0)};
	return {force, velocity};
}

