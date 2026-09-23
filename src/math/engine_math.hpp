#pragma once

#include <algorithm>

#include "resources/engine_spec.hpp"
#include "curve_math.hpp"

[[nodiscard]] double gross_torque_nm(double rpm, double throttle, const godot::EngineSpec &spec);

[[nodiscard]] double supercharger_boost_bar(double rpm, double throttle, const godot::EngineSpec &spec);
[[nodiscard]] double supercharger_drag_nm(double rpm, double throttle, const godot::EngineSpec &spec);

[[nodiscard]] double drag_torque_nm(double rpm, double throttle, const godot::EngineSpec &spec);
[[nodiscard]] double idle_control_torque_nm(double rpm, const godot::EngineSpec &spec);
