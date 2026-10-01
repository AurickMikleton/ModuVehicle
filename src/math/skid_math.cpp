#include "skid_math.hpp"

[[nodiscard]] double intensity(double slip_ratio, double slip_angle, double sliding_speed, double normal_load) {
	if (normal_load < 50.0) return 0.0;
	const double longitudinal {smoothstep(0.12, 0.55, std::abs(slip_ratio))};
	const double lateral {smoothstep(0.07, 0.30, std::abs(slip_angle))};
	return std::max(longitudinal, lateral) * smoothstep(0.25, 1.5, sliding_speed);
}
