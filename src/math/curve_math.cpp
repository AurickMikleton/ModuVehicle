#include "curve_math.hpp"

[[nodiscard]] double sample_uniform(const godot::PackedFloat32Array samples, double normalized_x) {
	const std::int64_t count = samples.size;
	const std::int64_t last = count - 1;
	if (count == 0) return 0.0;
	if (count == 1) return samples[0];

	if (std::isnan(normalized_x)) normalized_x = 0.0;
	const double x = std::clamp(normalized_x, 0.0, 1.0) * static_cast<double>(last);

	const int64_t lower = static_cast<int64_t>(x);
	const int64_t upper = std::min(lower + 1, last);

	const double weight = x - static_cast<double>(lower);

	const double a = samples[lower];
	const double b = samples[upper];

	return std::lerp(a, b, weight);
}

[[nodiscard]] double smoothstep(double edge_a, double edge_b, double x) {
	if godot::Math::is_equal_approx(edge_a, edge_b)
		return (x >= edge_b) ? 1.0 : 0.0;

	const double t = std::clamp(
		(x - edge_a) / (edge_b - edge_a),
		0.0,
		1.0
	);

	return t * t * (3.0 - 2.0 * t);
}


