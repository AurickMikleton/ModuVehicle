#include "vehicle_assembly.hpp"

namespace godot {

VehicleAssembly::VehicleAssembly() {
}

void VehicleAssembly::_bind_methods() {
    // godot-cpp requires a getter even for non-value category entries.
    ClassDB::bind_method(D_METHOD("_get_inspector_category"), &VehicleAssembly::_get_inspector_category);
    ADD_PROPERTY(PropertyInfo(Variant::NIL, "Identity", PROPERTY_HINT_NONE,
        "", PROPERTY_USAGE_CATEGORY), "", "_get_inspector_category");

    ClassDB::bind_method(D_METHOD("set_display_name", "value"), &VehicleAssembly::set_display_name);
    ClassDB::bind_method(D_METHOD("get_display_name"), &VehicleAssembly::get_display_name);
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "display_name"),
        "set_display_name", "get_display_name");

    ClassDB::bind_method(D_METHOD("set_vehicle_kind", "value"), &VehicleAssembly::set_vehicle_kind);
    ClassDB::bind_method(D_METHOD("get_vehicle_kind"), &VehicleAssembly::get_vehicle_kind);
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "vehicle_kind", PROPERTY_HINT_ENUM, "car,motorcycle,custom"),
        "set_vehicle_kind", "get_vehicle_kind");

    ADD_PROPERTY(PropertyInfo(Variant::NIL, "Components", PROPERTY_HINT_NONE,
        "", PROPERTY_USAGE_CATEGORY), "", "_get_inspector_category");

    ClassDB::bind_method(D_METHOD("set_chassis", "value"), &VehicleAssembly::set_chassis);
    ClassDB::bind_method(D_METHOD("get_chassis"), &VehicleAssembly::get_chassis);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "chassis", PROPERTY_HINT_RESOURCE_TYPE, "ChassisSpec"),
        "set_chassis", "get_chassis");

    ClassDB::bind_method(D_METHOD("set_engine", "value"), &VehicleAssembly::set_engine);
    ClassDB::bind_method(D_METHOD("get_engine"), &VehicleAssembly::get_engine);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "engine", PROPERTY_HINT_RESOURCE_TYPE, "EngineSpec"),
        "set_engine", "get_engine");

    ClassDB::bind_method(D_METHOD("set_gearbox", "value"), &VehicleAssembly::set_gearbox);
    ClassDB::bind_method(D_METHOD("get_gearbox"), &VehicleAssembly::get_gearbox);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "gearbox", PROPERTY_HINT_RESOURCE_TYPE, "GearboxSpec"),
        "set_gearbox", "get_gearbox");

    ClassDB::bind_method(D_METHOD("set_differential", "value"), &VehicleAssembly::set_differential);
    ClassDB::bind_method(D_METHOD("get_differential"), &VehicleAssembly::get_differential);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "differential", PROPERTY_HINT_RESOURCE_TYPE, "DifferentialSpec"),
        "set_differential", "get_differential");

    ClassDB::bind_method(D_METHOD("set_aero", "value"), &VehicleAssembly::set_aero);
    ClassDB::bind_method(D_METHOD("get_aero"), &VehicleAssembly::get_aero);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "aero", PROPERTY_HINT_RESOURCE_TYPE, "AeroSpec"),
        "set_aero", "get_aero");

    ClassDB::bind_method(D_METHOD("set_assists", "value"), &VehicleAssembly::set_assists);
    ClassDB::bind_method(D_METHOD("get_assists"), &VehicleAssembly::get_assists);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "assists", PROPERTY_HINT_RESOURCE_TYPE, "AssistSpec"),
        "set_assists", "get_assists");

    ClassDB::bind_method(D_METHOD("set_audio", "value"), &VehicleAssembly::set_audio);
    ClassDB::bind_method(D_METHOD("get_audio"), &VehicleAssembly::get_audio);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "audio", PROPERTY_HINT_RESOURCE_TYPE, "VehicleAudioSpec"),
        "set_audio", "get_audio");

    ClassDB::bind_method(D_METHOD("set_wheels", "value"), &VehicleAssembly::set_wheels);
    ClassDB::bind_method(D_METHOD("get_wheels"), &VehicleAssembly::get_wheels);
    ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "wheels", PROPERTY_HINT_ARRAY_TYPE, String::num_int64(Variant::OBJECT) + "/" +
            String::num_int64(PROPERTY_HINT_RESOURCE_TYPE) + ":WheelModuleSpec"),
        "set_wheels", "get_wheels");

    ADD_PROPERTY(PropertyInfo(Variant::NIL, "Controls", PROPERTY_HINT_NONE,
        "", PROPERTY_USAGE_CATEGORY), "", "_get_inspector_category");

    ClassDB::bind_method(D_METHOD("set_maximum_steering_degrees", "value"), &VehicleAssembly::set_maximum_steering_degrees);
    ClassDB::bind_method(D_METHOD("get_maximum_steering_degrees"), &VehicleAssembly::get_maximum_steering_degrees);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "maximum_steering_degrees", PROPERTY_HINT_RANGE, "1.0,60.0,0.5"),
        "set_maximum_steering_degrees", "get_maximum_steering_degrees");

    ClassDB::bind_method(D_METHOD("set_service_brake_torque_nm", "value"), &VehicleAssembly::set_service_brake_torque_nm);
    ClassDB::bind_method(D_METHOD("get_service_brake_torque_nm"), &VehicleAssembly::get_service_brake_torque_nm);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "service_brake_torque_nm", PROPERTY_HINT_RANGE, "100.0,30000.0,100.0"),
        "set_service_brake_torque_nm", "get_service_brake_torque_nm");

    ClassDB::bind_method(D_METHOD("set_handbrake_torque_nm", "value"), &VehicleAssembly::set_handbrake_torque_nm);
    ClassDB::bind_method(D_METHOD("get_handbrake_torque_nm"), &VehicleAssembly::get_handbrake_torque_nm);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "handbrake_torque_nm", PROPERTY_HINT_RANGE, "100.0,30000.0,100.0"),
        "set_handbrake_torque_nm", "get_handbrake_torque_nm");

}

void VehicleAssembly::set_display_name(const String &value) {
    if (display_name == value) {
        return;
    }
    display_name = value;
    emit_changed();
}

String VehicleAssembly::get_display_name() const {
    return display_name;
}

void VehicleAssembly::set_vehicle_kind(const String &value) {
    if (vehicle_kind == value) {
        return;
    }
    vehicle_kind = value;
    emit_changed();
}

String VehicleAssembly::get_vehicle_kind() const {
    return vehicle_kind;
}

void VehicleAssembly::set_chassis(const Ref<ChassisSpec> &value) {
    if (chassis == value) {
        return;
    }
    chassis = value;
    emit_changed();
}

Ref<ChassisSpec> VehicleAssembly::get_chassis() const {
    return chassis;
}

void VehicleAssembly::set_engine(const Ref<EngineSpec> &value) {
    if (engine == value) {
        return;
    }
    engine = value;
    emit_changed();
}

Ref<EngineSpec> VehicleAssembly::get_engine() const {
    return engine;
}

void VehicleAssembly::set_gearbox(const Ref<GearboxSpec> &value) {
    if (gearbox == value) {
        return;
    }
    gearbox = value;
    emit_changed();
}

Ref<GearboxSpec> VehicleAssembly::get_gearbox() const {
    return gearbox;
}

void VehicleAssembly::set_differential(const Ref<DifferentialSpec> &value) {
    if (differential == value) {
        return;
    }
    differential = value;
    emit_changed();
}

Ref<DifferentialSpec> VehicleAssembly::get_differential() const {
    return differential;
}

void VehicleAssembly::set_aero(const Ref<AeroSpec> &value) {
    if (aero == value) {
        return;
    }
    aero = value;
    emit_changed();
}

Ref<AeroSpec> VehicleAssembly::get_aero() const {
    return aero;
}

void VehicleAssembly::set_assists(const Ref<AssistSpec> &value) {
    if (assists == value) {
        return;
    }
    assists = value;
    emit_changed();
}

Ref<AssistSpec> VehicleAssembly::get_assists() const {
    return assists;
}

void VehicleAssembly::set_audio(const Ref<VehicleAudioSpec> &value) {
    if (audio == value) {
        return;
    }
    audio = value;
    emit_changed();
}

Ref<VehicleAudioSpec> VehicleAssembly::get_audio() const {
    return audio;
}

void VehicleAssembly::set_wheels(const TypedArray<WheelModuleSpec> &value) {
    wheels = value;
    emit_changed();
}

TypedArray<WheelModuleSpec> VehicleAssembly::get_wheels() const {
    return wheels;
}

void VehicleAssembly::set_maximum_steering_degrees(double value) {
    if (maximum_steering_degrees == value) {
        return;
    }
    maximum_steering_degrees = value;
    emit_changed();
}

double VehicleAssembly::get_maximum_steering_degrees() const {
    return maximum_steering_degrees;
}

void VehicleAssembly::set_service_brake_torque_nm(double value) {
    if (service_brake_torque_nm == value) {
        return;
    }
    service_brake_torque_nm = value;
    emit_changed();
}

double VehicleAssembly::get_service_brake_torque_nm() const {
    return service_brake_torque_nm;
}

void VehicleAssembly::set_handbrake_torque_nm(double value) {
    if (handbrake_torque_nm == value) {
        return;
    }
    handbrake_torque_nm = value;
    emit_changed();
}

double VehicleAssembly::get_handbrake_torque_nm() const {
    return handbrake_torque_nm;
}

} // namespace godot

godot::Variant godot::VehicleAssembly::_get_inspector_category() const {
    return Variant();
}
