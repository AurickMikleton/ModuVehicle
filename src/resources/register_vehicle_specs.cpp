#include "register_vehicle_specs.hpp"
#include "aero_spec.hpp"
#include "assist_spec.hpp"
#include "chassis_spec.hpp"
#include "differential_spec.hpp"
#include "engine_sound_layout.hpp"
#include "engine_spec.hpp"
#include "gearbox_spec.hpp"
#include "suspension_spec.hpp"
#include "tire_spec.hpp"
#include "vehicle_audio_spec.hpp"
#include "wheel_module_spec.hpp"
#include "vehicle_assembly.hpp"

namespace godot {

void register_vehicle_specs() {
    ClassDB::register_class<AeroSpec>();
    ClassDB::register_class<AssistSpec>();
    ClassDB::register_class<ChassisSpec>();
    ClassDB::register_class<DifferentialSpec>();
    ClassDB::register_class<EngineSoundLayout>();
    ClassDB::register_class<EngineSpec>();
    ClassDB::register_class<GearboxSpec>();
    ClassDB::register_class<SuspensionSpec>();
    ClassDB::register_class<TireSpec>();
    ClassDB::register_class<VehicleAudioSpec>();
    ClassDB::register_class<WheelModuleSpec>();
    ClassDB::register_class<VehicleAssembly>();
}

} // namespace godot
