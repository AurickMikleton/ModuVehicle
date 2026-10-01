#include <cstdint>

struct VehicleState {
	double rpm;
	std::int64_t gear;
	double shift_timer;
	double shift_inhibit;
	double clutch_engagement;
	double clutch_slip_rpm;
	double clutch_torque_nm;
	double engine_torque_nm;
	double wheel_torque_nm;
	double engine_load;
	bool shifted;
};

constexpr double rad_to_rpm = 60.0 / Math_TAU;
constexpr double rpm_to_rad = Math_TAU / 60.0;

[[nodiscard]] double gear_ratio();

[[nodiscard]] VehicleState step();
