#pragma once

[[nodiscard]] double gross_torque_nm(double rpm, double throttle, EngineSpec spec);
[[nodiscard]] double drag_torque_nm(double rpm, double throttle, EngineSpec spec);
[[nodiscard]] double idle_control_torque_nm(double rpm, EngineSpec spec);

