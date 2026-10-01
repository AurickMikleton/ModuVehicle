#include "skid_math.hpp"

[[nodiscard]] double intensity(double slip_ratio, double slip_angle, double sliding_speed, double normal_load) {
	if (normal_load < 50.0) return 0.0; // below 50 nm of normal_load skid is disabled
	const double longitudinal {smoothstep(0.12, 0.55, std::abs(slip_ratio))}; // longitudinal skid intensity increases starting at 12% slip_ratio and maximizes intensity at 50% slip_ratio
	const double lateral {smoothstep(0.07, 0.30, std::abs(slip_angle))}; // lateral skid intensity increases starting at ~4 degrees of slip_angle and maximizes intensity at ~17.2 degrees of slip_angle
	return std::max(longitudinal, lateral) * smoothstep(0.25, 1.5, sliding_speed); // effect supressed below 0.25 m/s and is fully unsupressed above 1.5 m/s
}
