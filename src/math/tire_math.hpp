#include <godot_cpp/variant/vector2.hpp>
#include "resources/tire_spec.hpp"

[[nodiscard]] godot::vector2 combined_force(double slip_ratio, double slip_angle, double normal_load, const TireSpec &spec);
