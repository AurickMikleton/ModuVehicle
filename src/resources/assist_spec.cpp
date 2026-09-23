#include "assist_spec.hpp"

namespace godot {

AssistSpec::AssistSpec() {
}

void AssistSpec::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_traction_control", "value"), &AssistSpec::set_traction_control);
    ClassDB::bind_method(D_METHOD("get_traction_control"), &AssistSpec::get_traction_control);
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "traction_control"),
        "set_traction_control", "get_traction_control");

    ClassDB::bind_method(D_METHOD("set_target_drive_slip", "value"), &AssistSpec::set_target_drive_slip);
    ClassDB::bind_method(D_METHOD("get_target_drive_slip"), &AssistSpec::get_target_drive_slip);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "target_drive_slip", PROPERTY_HINT_RANGE, "0.0,1.0,0.01"),
        "set_target_drive_slip", "get_target_drive_slip");

    ClassDB::bind_method(D_METHOD("set_traction_control_gain", "value"), &AssistSpec::set_traction_control_gain);
    ClassDB::bind_method(D_METHOD("get_traction_control_gain"), &AssistSpec::get_traction_control_gain);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "traction_control_gain", PROPERTY_HINT_RANGE, "0.0,20.0,0.1"),
        "set_traction_control_gain", "get_traction_control_gain");

    ClassDB::bind_method(D_METHOD("set_stability_assist", "value"), &AssistSpec::set_stability_assist);
    ClassDB::bind_method(D_METHOD("get_stability_assist"), &AssistSpec::get_stability_assist);
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "stability_assist"),
        "set_stability_assist", "get_stability_assist");

    ClassDB::bind_method(D_METHOD("set_yaw_damping_torque", "value"), &AssistSpec::set_yaw_damping_torque);
    ClassDB::bind_method(D_METHOD("get_yaw_damping_torque"), &AssistSpec::get_yaw_damping_torque);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "yaw_damping_torque", PROPERTY_HINT_RANGE, "0.0,5000.0,10.0"),
        "set_yaw_damping_torque", "get_yaw_damping_torque");

    ClassDB::bind_method(D_METHOD("set_motorcycle_balance_assist", "value"), &AssistSpec::set_motorcycle_balance_assist);
    ClassDB::bind_method(D_METHOD("get_motorcycle_balance_assist"), &AssistSpec::get_motorcycle_balance_assist);
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "motorcycle_balance_assist"),
        "set_motorcycle_balance_assist", "get_motorcycle_balance_assist");

    ClassDB::bind_method(D_METHOD("set_balance_strength", "value"), &AssistSpec::set_balance_strength);
    ClassDB::bind_method(D_METHOD("get_balance_strength"), &AssistSpec::get_balance_strength);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "balance_strength", PROPERTY_HINT_RANGE, "0.0,10000.0,10.0"),
        "set_balance_strength", "get_balance_strength");

    ClassDB::bind_method(D_METHOD("set_balance_damping", "value"), &AssistSpec::set_balance_damping);
    ClassDB::bind_method(D_METHOD("get_balance_damping"), &AssistSpec::get_balance_damping);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "balance_damping", PROPERTY_HINT_RANGE, "0.0,5000.0,10.0"),
        "set_balance_damping", "get_balance_damping");

}

void AssistSpec::set_traction_control(bool value) {
    if (traction_control == value) {
        return;
    }
    traction_control = value;
    emit_changed();
}

bool AssistSpec::get_traction_control() const {
    return traction_control;
}

void AssistSpec::set_target_drive_slip(double value) {
    if (target_drive_slip == value) {
        return;
    }
    target_drive_slip = value;
    emit_changed();
}

double AssistSpec::get_target_drive_slip() const {
    return target_drive_slip;
}

void AssistSpec::set_traction_control_gain(double value) {
    if (traction_control_gain == value) {
        return;
    }
    traction_control_gain = value;
    emit_changed();
}

double AssistSpec::get_traction_control_gain() const {
    return traction_control_gain;
}

void AssistSpec::set_stability_assist(bool value) {
    if (stability_assist == value) {
        return;
    }
    stability_assist = value;
    emit_changed();
}

bool AssistSpec::get_stability_assist() const {
    return stability_assist;
}

void AssistSpec::set_yaw_damping_torque(double value) {
    if (yaw_damping_torque == value) {
        return;
    }
    yaw_damping_torque = value;
    emit_changed();
}

double AssistSpec::get_yaw_damping_torque() const {
    return yaw_damping_torque;
}

void AssistSpec::set_motorcycle_balance_assist(bool value) {
    if (motorcycle_balance_assist == value) {
        return;
    }
    motorcycle_balance_assist = value;
    emit_changed();
}

bool AssistSpec::get_motorcycle_balance_assist() const {
    return motorcycle_balance_assist;
}

void AssistSpec::set_balance_strength(double value) {
    if (balance_strength == value) {
        return;
    }
    balance_strength = value;
    emit_changed();
}

double AssistSpec::get_balance_strength() const {
    return balance_strength;
}

void AssistSpec::set_balance_damping(double value) {
    if (balance_damping == value) {
        return;
    }
    balance_damping = value;
    emit_changed();
}

double AssistSpec::get_balance_damping() const {
    return balance_damping;
}

} // namespace godot
