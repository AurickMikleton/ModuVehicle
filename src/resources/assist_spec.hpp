#pragma once

#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/variant/string.hpp>
#include <godot_cpp/variant/vector3.hpp>
#include <godot_cpp/variant/packed_float32_array.hpp>
#include <godot_cpp/variant/typed_array.hpp>
#include <cstdint>

namespace godot {

class AssistSpec : public Resource {
    GDCLASS(AssistSpec, Resource)

private:
    bool traction_control = true;
    double target_drive_slip = 0.14;
    // Legacy preset compatibility; the implicit traction torque cap uses target_drive_slip.
    double traction_control_gain = 5.0;
    bool stability_assist = true;
    double yaw_damping_torque = 850.0;
    bool motorcycle_balance_assist = false;
    double balance_strength = 2200.0;
    double balance_damping = 380.0;

protected:
    static void _bind_methods();

public:
    AssistSpec();

    void set_traction_control(bool value);
    bool get_traction_control() const;

    void set_target_drive_slip(double value);
    double get_target_drive_slip() const;

    void set_traction_control_gain(double value);
    double get_traction_control_gain() const;

    void set_stability_assist(bool value);
    bool get_stability_assist() const;

    void set_yaw_damping_torque(double value);
    double get_yaw_damping_torque() const;

    void set_motorcycle_balance_assist(bool value);
    bool get_motorcycle_balance_assist() const;

    void set_balance_strength(double value);
    double get_balance_strength() const;

    void set_balance_damping(double value);
    double get_balance_damping() const;

};

} // namespace godot
