#include "resources/aero_spec.hpp"
#include <godot_cpp/variant/vector3.hpp>

inline constexpr double k_air_density {1.225};

[[nodiscard]] godot::Vector3 drag_force(godot::Vector3 velocity, const godot::AeroSpec &spec);
[[nodiscard]] double downforce(double speed, const godot::AeroSpec &spec);
