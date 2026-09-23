#pragma once

#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/variant/string.hpp>
#include <godot_cpp/variant/vector3.hpp>
#include <godot_cpp/variant/packed_float32_array.hpp>
#include <godot_cpp/variant/typed_array.hpp>
#include <cstdint>
#include "aero_spec.hpp"
#include "assist_spec.hpp"
#include "chassis_spec.hpp"
#include "differential_spec.hpp"
#include "engine_spec.hpp"
#include "gearbox_spec.hpp"
#include "vehicle_audio_spec.hpp"
#include "wheel_module_spec.hpp"

namespace godot {

class VehicleAssembly : public Resource {
    GDCLASS(VehicleAssembly, Resource)

private:

    // Identity
    String display_name = "Modular Vehicle";
    String vehicle_kind = "car";

    // Components
    Ref<ChassisSpec> chassis;
    Ref<EngineSpec> engine;
    Ref<GearboxSpec> gearbox;
    Ref<DifferentialSpec> differential;
    Ref<AeroSpec> aero;
    Ref<AssistSpec> assists;
    Ref<VehicleAudioSpec> audio;
    TypedArray<WheelModuleSpec> wheels;

    // Controls
    double maximum_steering_degrees = 28.0;
    double service_brake_torque_nm = 4200.0;
    double handbrake_torque_nm = 5200.0;

protected:
    static void _bind_methods();
    Variant _get_inspector_category() const;

public:
    VehicleAssembly();

    void set_display_name(const String &value);
    String get_display_name() const;

    void set_vehicle_kind(const String &value);
    String get_vehicle_kind() const;

    void set_chassis(const Ref<ChassisSpec> &value);
    Ref<ChassisSpec> get_chassis() const;

    void set_engine(const Ref<EngineSpec> &value);
    Ref<EngineSpec> get_engine() const;

    void set_gearbox(const Ref<GearboxSpec> &value);
    Ref<GearboxSpec> get_gearbox() const;

    void set_differential(const Ref<DifferentialSpec> &value);
    Ref<DifferentialSpec> get_differential() const;

    void set_aero(const Ref<AeroSpec> &value);
    Ref<AeroSpec> get_aero() const;

    void set_assists(const Ref<AssistSpec> &value);
    Ref<AssistSpec> get_assists() const;

    void set_audio(const Ref<VehicleAudioSpec> &value);
    Ref<VehicleAudioSpec> get_audio() const;

    void set_wheels(const TypedArray<WheelModuleSpec> &value);
    TypedArray<WheelModuleSpec> get_wheels() const;

    void set_maximum_steering_degrees(double value);
    double get_maximum_steering_degrees() const;

    void set_service_brake_torque_nm(double value);
    double get_service_brake_torque_nm() const;

    void set_handbrake_torque_nm(double value);
    double get_handbrake_torque_nm() const;

};

} // namespace godot
