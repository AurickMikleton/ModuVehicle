#include <algorithm>
#include "resources/suspension_spec.hpp"

struct SuspensionForceResult {
	double force;
	double compression_velocity;
};

[[nodiscard]] SuspensionForceResult normal_force(double compression, double previous_compression, double delta, const godot::SuspensionSpec spec);
