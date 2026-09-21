#pragma once

#include <godot_cpp/variant/packed_float32_array.hpp>
#include <godot_cpp/core/math.hpp>
#include <algorithm>
#include <cmath>
#include <cstdint>

[[nodiscard]] double sample_uniform(const godot::PackedFloat32Array samples, double normalized_x);
[[nodiscard]] double smoothstep(double edge_a, double edge_b, double x);
