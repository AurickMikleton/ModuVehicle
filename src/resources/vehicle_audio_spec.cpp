#include "vehicle_audio_spec.hpp"

namespace godot {

VehicleAudioSpec::VehicleAudioSpec() {
}

void VehicleAudioSpec::_bind_methods() {
    // godot-cpp requires a getter even for non-value category entries.
    ClassDB::bind_method(D_METHOD("_get_inspector_category"), &VehicleAudioSpec::_get_inspector_category);
    ADD_PROPERTY(PropertyInfo(Variant::NIL, "Engine sound", PROPERTY_HINT_NONE,
        "", PROPERTY_USAGE_CATEGORY), "", "_get_inspector_category");

    ClassDB::bind_method(D_METHOD("set_engine_layout", "value"), &VehicleAudioSpec::set_engine_layout);
    ClassDB::bind_method(D_METHOD("get_engine_layout"), &VehicleAudioSpec::get_engine_layout);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "engine_layout", PROPERTY_HINT_RESOURCE_TYPE, "EngineSoundLayout"),
        "set_engine_layout", "get_engine_layout");

    ADD_PROPERTY(PropertyInfo(Variant::NIL, "Layers", PROPERTY_HINT_NONE,
        "", PROPERTY_USAGE_CATEGORY), "", "_get_inspector_category");

    ClassDB::bind_method(D_METHOD("set_engine_enabled", "value"), &VehicleAudioSpec::set_engine_enabled);
    ClassDB::bind_method(D_METHOD("get_engine_enabled"), &VehicleAudioSpec::get_engine_enabled);
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "engine_enabled"),
        "set_engine_enabled", "get_engine_enabled");

    ClassDB::bind_method(D_METHOD("set_transmission_enabled", "value"), &VehicleAudioSpec::set_transmission_enabled);
    ClassDB::bind_method(D_METHOD("get_transmission_enabled"), &VehicleAudioSpec::get_transmission_enabled);
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "transmission_enabled"),
        "set_transmission_enabled", "get_transmission_enabled");

    ClassDB::bind_method(D_METHOD("set_burble_enabled", "value"), &VehicleAudioSpec::set_burble_enabled);
    ClassDB::bind_method(D_METHOD("get_burble_enabled"), &VehicleAudioSpec::get_burble_enabled);
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "burble_enabled"),
        "set_burble_enabled", "get_burble_enabled");

    ClassDB::bind_method(D_METHOD("set_turbo_enabled", "value"), &VehicleAudioSpec::set_turbo_enabled);
    ClassDB::bind_method(D_METHOD("get_turbo_enabled"), &VehicleAudioSpec::get_turbo_enabled);
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "turbo_enabled"),
        "set_turbo_enabled", "get_turbo_enabled");

    ClassDB::bind_method(D_METHOD("set_blowoff_enabled", "value"), &VehicleAudioSpec::set_blowoff_enabled);
    ClassDB::bind_method(D_METHOD("get_blowoff_enabled"), &VehicleAudioSpec::get_blowoff_enabled);
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "blowoff_enabled"),
        "set_blowoff_enabled", "get_blowoff_enabled");

    ClassDB::bind_method(D_METHOD("set_shift_enabled", "value"), &VehicleAudioSpec::set_shift_enabled);
    ClassDB::bind_method(D_METHOD("get_shift_enabled"), &VehicleAudioSpec::get_shift_enabled);
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "shift_enabled"),
        "set_shift_enabled", "get_shift_enabled");

    ClassDB::bind_method(D_METHOD("set_supercharger_enabled", "value"), &VehicleAudioSpec::set_supercharger_enabled);
    ClassDB::bind_method(D_METHOD("get_supercharger_enabled"), &VehicleAudioSpec::get_supercharger_enabled);
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "supercharger_enabled"),
        "set_supercharger_enabled", "get_supercharger_enabled");

    ClassDB::bind_method(D_METHOD("set_master_level", "value"), &VehicleAudioSpec::set_master_level);
    ClassDB::bind_method(D_METHOD("get_master_level"), &VehicleAudioSpec::get_master_level);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "master_level", PROPERTY_HINT_RANGE, "0.0,1.0,0.01"),
        "set_master_level", "get_master_level");

    ClassDB::bind_method(D_METHOD("set_engine_level", "value"), &VehicleAudioSpec::set_engine_level);
    ClassDB::bind_method(D_METHOD("get_engine_level"), &VehicleAudioSpec::get_engine_level);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "engine_level", PROPERTY_HINT_RANGE, "0.0,1.0,0.01"),
        "set_engine_level", "get_engine_level");

    ClassDB::bind_method(D_METHOD("set_transmission_level", "value"), &VehicleAudioSpec::set_transmission_level);
    ClassDB::bind_method(D_METHOD("get_transmission_level"), &VehicleAudioSpec::get_transmission_level);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "transmission_level", PROPERTY_HINT_RANGE, "0.0,1.0,0.01"),
        "set_transmission_level", "get_transmission_level");

    ClassDB::bind_method(D_METHOD("set_turbo_level", "value"), &VehicleAudioSpec::set_turbo_level);
    ClassDB::bind_method(D_METHOD("get_turbo_level"), &VehicleAudioSpec::get_turbo_level);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "turbo_level", PROPERTY_HINT_RANGE, "0.0,1.0,0.01"),
        "set_turbo_level", "get_turbo_level");

    ClassDB::bind_method(D_METHOD("set_shift_level", "value"), &VehicleAudioSpec::set_shift_level);
    ClassDB::bind_method(D_METHOD("get_shift_level"), &VehicleAudioSpec::get_shift_level);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "shift_level", PROPERTY_HINT_RANGE, "0.0,1.0,0.01"),
        "set_shift_level", "get_shift_level");

    ADD_PROPERTY(PropertyInfo(Variant::NIL, "Exhaust and intake", PROPERTY_HINT_NONE,
        "", PROPERTY_USAGE_CATEGORY), "", "_get_inspector_category");

    ClassDB::bind_method(D_METHOD("set_duty_cycle", "value"), &VehicleAudioSpec::set_duty_cycle);
    ClassDB::bind_method(D_METHOD("get_duty_cycle"), &VehicleAudioSpec::get_duty_cycle);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "duty_cycle", PROPERTY_HINT_RANGE, "0.05,0.8,0.01"),
        "set_duty_cycle", "get_duty_cycle");

    ClassDB::bind_method(D_METHOD("set_pattern_strength", "value"), &VehicleAudioSpec::set_pattern_strength);
    ClassDB::bind_method(D_METHOD("get_pattern_strength"), &VehicleAudioSpec::get_pattern_strength);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "pattern_strength", PROPERTY_HINT_RANGE, "0.0,1.0,0.01"),
        "set_pattern_strength", "get_pattern_strength");

    ClassDB::bind_method(D_METHOD("set_rumble_resonance", "value"), &VehicleAudioSpec::set_rumble_resonance);
    ClassDB::bind_method(D_METHOD("get_rumble_resonance"), &VehicleAudioSpec::get_rumble_resonance);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "rumble_resonance", PROPERTY_HINT_RANGE, "0.0,1.0,0.01"),
        "set_rumble_resonance", "get_rumble_resonance");

    ClassDB::bind_method(D_METHOD("set_muffler_resonance_hz", "value"), &VehicleAudioSpec::set_muffler_resonance_hz);
    ClassDB::bind_method(D_METHOD("get_muffler_resonance_hz"), &VehicleAudioSpec::get_muffler_resonance_hz);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "muffler_resonance_hz", PROPERTY_HINT_RANGE, "50.0,500.0,1.0"),
        "set_muffler_resonance_hz", "get_muffler_resonance_hz");

    ClassDB::bind_method(D_METHOD("set_muffler_damping", "value"), &VehicleAudioSpec::set_muffler_damping);
    ClassDB::bind_method(D_METHOD("get_muffler_damping"), &VehicleAudioSpec::get_muffler_damping);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "muffler_damping", PROPERTY_HINT_RANGE, "0.05,0.95,0.01"),
        "set_muffler_damping", "get_muffler_damping");

    ClassDB::bind_method(D_METHOD("set_tailpipe_lowpass_hz", "value"), &VehicleAudioSpec::set_tailpipe_lowpass_hz);
    ClassDB::bind_method(D_METHOD("get_tailpipe_lowpass_hz"), &VehicleAudioSpec::get_tailpipe_lowpass_hz);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "tailpipe_lowpass_hz", PROPERTY_HINT_RANGE, "200.0,16000.0,100.0"),
        "set_tailpipe_lowpass_hz", "get_tailpipe_lowpass_hz");

    ClassDB::bind_method(D_METHOD("set_exhaust_echo_strength", "value"), &VehicleAudioSpec::set_exhaust_echo_strength);
    ClassDB::bind_method(D_METHOD("get_exhaust_echo_strength"), &VehicleAudioSpec::get_exhaust_echo_strength);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "exhaust_echo_strength", PROPERTY_HINT_RANGE, "0.0,0.8,0.01"),
        "set_exhaust_echo_strength", "get_exhaust_echo_strength");

    ClassDB::bind_method(D_METHOD("set_throttle_intake_gain", "value"), &VehicleAudioSpec::set_throttle_intake_gain);
    ClassDB::bind_method(D_METHOD("get_throttle_intake_gain"), &VehicleAudioSpec::get_throttle_intake_gain);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "throttle_intake_gain", PROPERTY_HINT_RANGE, "0.0,1.0,0.01"),
        "set_throttle_intake_gain", "get_throttle_intake_gain");

    ClassDB::bind_method(D_METHOD("set_burble_intensity", "value"), &VehicleAudioSpec::set_burble_intensity);
    ClassDB::bind_method(D_METHOD("get_burble_intensity"), &VehicleAudioSpec::get_burble_intensity);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "burble_intensity", PROPERTY_HINT_RANGE, "0.0,3.0,0.05"),
        "set_burble_intensity", "get_burble_intensity");

    ClassDB::bind_method(D_METHOD("set_burble_presence", "value"), &VehicleAudioSpec::set_burble_presence);
    ClassDB::bind_method(D_METHOD("get_burble_presence"), &VehicleAudioSpec::get_burble_presence);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "burble_presence", PROPERTY_HINT_RANGE, "0.0,1.0,0.01"),
        "set_burble_presence", "get_burble_presence");

    ClassDB::bind_method(D_METHOD("set_burble_lift_duration", "value"), &VehicleAudioSpec::set_burble_lift_duration);
    ClassDB::bind_method(D_METHOD("get_burble_lift_duration"), &VehicleAudioSpec::get_burble_lift_duration);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "burble_lift_duration", PROPERTY_HINT_RANGE, "0.1,3.0,0.05"),
        "set_burble_lift_duration", "get_burble_lift_duration");

    ADD_PROPERTY(PropertyInfo(Variant::NIL, "Turbo and blow-off", PROPERTY_HINT_NONE,
        "", PROPERTY_USAGE_CATEGORY), "", "_get_inspector_category");

    ClassDB::bind_method(D_METHOD("set_turbo_base_pitch_hz", "value"), &VehicleAudioSpec::set_turbo_base_pitch_hz);
    ClassDB::bind_method(D_METHOD("get_turbo_base_pitch_hz"), &VehicleAudioSpec::get_turbo_base_pitch_hz);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "turbo_base_pitch_hz", PROPERTY_HINT_RANGE, "100.0,3000.0,10.0"),
        "set_turbo_base_pitch_hz", "get_turbo_base_pitch_hz");

    ClassDB::bind_method(D_METHOD("set_turbo_max_pitch_hz", "value"), &VehicleAudioSpec::set_turbo_max_pitch_hz);
    ClassDB::bind_method(D_METHOD("get_turbo_max_pitch_hz"), &VehicleAudioSpec::get_turbo_max_pitch_hz);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "turbo_max_pitch_hz", PROPERTY_HINT_RANGE, "1000.0,10000.0,100.0"),
        "set_turbo_max_pitch_hz", "get_turbo_max_pitch_hz");

    ClassDB::bind_method(D_METHOD("set_turbo_induction_gain", "value"), &VehicleAudioSpec::set_turbo_induction_gain);
    ClassDB::bind_method(D_METHOD("get_turbo_induction_gain"), &VehicleAudioSpec::get_turbo_induction_gain);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "turbo_induction_gain", PROPERTY_HINT_RANGE, "0.0,1.0,0.01"),
        "set_turbo_induction_gain", "get_turbo_induction_gain");

    ClassDB::bind_method(D_METHOD("set_blowoff_gain", "value"), &VehicleAudioSpec::set_blowoff_gain);
    ClassDB::bind_method(D_METHOD("get_blowoff_gain"), &VehicleAudioSpec::get_blowoff_gain);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "blowoff_gain", PROPERTY_HINT_RANGE, "0.0,2.0,0.01"),
        "set_blowoff_gain", "get_blowoff_gain");

    ClassDB::bind_method(D_METHOD("set_blowoff_decay_rate", "value"), &VehicleAudioSpec::set_blowoff_decay_rate);
    ClassDB::bind_method(D_METHOD("get_blowoff_decay_rate"), &VehicleAudioSpec::get_blowoff_decay_rate);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "blowoff_decay_rate", PROPERTY_HINT_RANGE, "1.0,20.0,0.1"),
        "set_blowoff_decay_rate", "get_blowoff_decay_rate");

    ADD_PROPERTY(PropertyInfo(Variant::NIL, "Supercharger", PROPERTY_HINT_NONE,
        "", PROPERTY_USAGE_CATEGORY), "", "_get_inspector_category");

    ClassDB::bind_method(D_METHOD("set_supercharger_style", "value"), &VehicleAudioSpec::set_supercharger_style);
    ClassDB::bind_method(D_METHOD("get_supercharger_style"), &VehicleAudioSpec::get_supercharger_style);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "supercharger_style", PROPERTY_HINT_ENUM, "Roots / twin-screw,Centrifugal"),
        "set_supercharger_style", "get_supercharger_style");

    ClassDB::bind_method(D_METHOD("set_supercharger_level", "value"), &VehicleAudioSpec::set_supercharger_level);
    ClassDB::bind_method(D_METHOD("get_supercharger_level"), &VehicleAudioSpec::get_supercharger_level);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "supercharger_level", PROPERTY_HINT_RANGE, "0.0,1.0,0.01"),
        "set_supercharger_level", "get_supercharger_level");

    ClassDB::bind_method(D_METHOD("set_supercharger_blowoff_enabled", "value"), &VehicleAudioSpec::set_supercharger_blowoff_enabled);
    ClassDB::bind_method(D_METHOD("get_supercharger_blowoff_enabled"), &VehicleAudioSpec::get_supercharger_blowoff_enabled);
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "supercharger_blowoff_enabled"),
        "set_supercharger_blowoff_enabled", "get_supercharger_blowoff_enabled");

    ClassDB::bind_method(D_METHOD("set_centrifugal_max_pitch_hz", "value"), &VehicleAudioSpec::set_centrifugal_max_pitch_hz);
    ClassDB::bind_method(D_METHOD("get_centrifugal_max_pitch_hz"), &VehicleAudioSpec::get_centrifugal_max_pitch_hz);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "centrifugal_max_pitch_hz", PROPERTY_HINT_RANGE, "500.0,10000.0,100.0"),
        "set_centrifugal_max_pitch_hz", "get_centrifugal_max_pitch_hz");

    ClassDB::bind_method(D_METHOD("set_centrifugal_air_gain", "value"), &VehicleAudioSpec::set_centrifugal_air_gain);
    ClassDB::bind_method(D_METHOD("get_centrifugal_air_gain"), &VehicleAudioSpec::get_centrifugal_air_gain);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "centrifugal_air_gain", PROPERTY_HINT_RANGE, "0.0,1.0,0.01"),
        "set_centrifugal_air_gain", "get_centrifugal_air_gain");

    ClassDB::bind_method(D_METHOD("set_centrifugal_tone_gain", "value"), &VehicleAudioSpec::set_centrifugal_tone_gain);
    ClassDB::bind_method(D_METHOD("get_centrifugal_tone_gain"), &VehicleAudioSpec::get_centrifugal_tone_gain);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "centrifugal_tone_gain", PROPERTY_HINT_RANGE, "0.0,1.0,0.01"),
        "set_centrifugal_tone_gain", "get_centrifugal_tone_gain");

    ClassDB::bind_method(D_METHOD("set_centrifugal_bypass_gain", "value"), &VehicleAudioSpec::set_centrifugal_bypass_gain);
    ClassDB::bind_method(D_METHOD("get_centrifugal_bypass_gain"), &VehicleAudioSpec::get_centrifugal_bypass_gain);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "centrifugal_bypass_gain", PROPERTY_HINT_RANGE, "0.0,1.0,0.01"),
        "set_centrifugal_bypass_gain", "get_centrifugal_bypass_gain");

    ClassDB::bind_method(D_METHOD("set_centrifugal_air_cutoff_hz", "value"), &VehicleAudioSpec::set_centrifugal_air_cutoff_hz);
    ClassDB::bind_method(D_METHOD("get_centrifugal_air_cutoff_hz"), &VehicleAudioSpec::get_centrifugal_air_cutoff_hz);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "centrifugal_air_cutoff_hz", PROPERTY_HINT_RANGE, "1000.0,10000.0,100.0"),
        "set_centrifugal_air_cutoff_hz", "get_centrifugal_air_cutoff_hz");

    ClassDB::bind_method(D_METHOD("set_blowoff_tone_gain", "value"), &VehicleAudioSpec::set_blowoff_tone_gain);
    ClassDB::bind_method(D_METHOD("get_blowoff_tone_gain"), &VehicleAudioSpec::get_blowoff_tone_gain);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "blowoff_tone_gain", PROPERTY_HINT_RANGE, "0.0,1.0,0.01"),
        "set_blowoff_tone_gain", "get_blowoff_tone_gain");

    ClassDB::bind_method(D_METHOD("set_blowoff_flutter_depth", "value"), &VehicleAudioSpec::set_blowoff_flutter_depth);
    ClassDB::bind_method(D_METHOD("get_blowoff_flutter_depth"), &VehicleAudioSpec::get_blowoff_flutter_depth);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "blowoff_flutter_depth", PROPERTY_HINT_RANGE, "0.0,1.0,0.01"),
        "set_blowoff_flutter_depth", "get_blowoff_flutter_depth");

    ClassDB::bind_method(D_METHOD("set_supercharger_drive_ratio", "value"), &VehicleAudioSpec::set_supercharger_drive_ratio);
    ClassDB::bind_method(D_METHOD("get_supercharger_drive_ratio"), &VehicleAudioSpec::get_supercharger_drive_ratio);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "supercharger_drive_ratio", PROPERTY_HINT_RANGE, "0.5,5.0,0.05"),
        "set_supercharger_drive_ratio", "get_supercharger_drive_ratio");

    ClassDB::bind_method(D_METHOD("set_supercharger_lobes", "value"), &VehicleAudioSpec::set_supercharger_lobes);
    ClassDB::bind_method(D_METHOD("get_supercharger_lobes"), &VehicleAudioSpec::get_supercharger_lobes);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "supercharger_lobes", PROPERTY_HINT_RANGE, "2,12,1"),
        "set_supercharger_lobes", "get_supercharger_lobes");

    ClassDB::bind_method(D_METHOD("set_supercharger_harmonics", "value"), &VehicleAudioSpec::set_supercharger_harmonics);
    ClassDB::bind_method(D_METHOD("get_supercharger_harmonics"), &VehicleAudioSpec::get_supercharger_harmonics);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "supercharger_harmonics", PROPERTY_HINT_RANGE, "0.0,1.0,0.01"),
        "set_supercharger_harmonics", "get_supercharger_harmonics");

}

void VehicleAudioSpec::set_engine_layout(const Ref<EngineSoundLayout> &value) {
    if (engine_layout == value) {
        return;
    }
    engine_layout = value;
    emit_changed();
}

Ref<EngineSoundLayout> VehicleAudioSpec::get_engine_layout() const {
    return engine_layout;
}

void VehicleAudioSpec::set_engine_enabled(bool value) {
    if (engine_enabled == value) {
        return;
    }
    engine_enabled = value;
    emit_changed();
}

bool VehicleAudioSpec::get_engine_enabled() const {
    return engine_enabled;
}

void VehicleAudioSpec::set_transmission_enabled(bool value) {
    if (transmission_enabled == value) {
        return;
    }
    transmission_enabled = value;
    emit_changed();
}

bool VehicleAudioSpec::get_transmission_enabled() const {
    return transmission_enabled;
}

void VehicleAudioSpec::set_burble_enabled(bool value) {
    if (burble_enabled == value) {
        return;
    }
    burble_enabled = value;
    emit_changed();
}

bool VehicleAudioSpec::get_burble_enabled() const {
    return burble_enabled;
}

void VehicleAudioSpec::set_turbo_enabled(bool value) {
    if (turbo_enabled == value) {
        return;
    }
    turbo_enabled = value;
    emit_changed();
}

bool VehicleAudioSpec::get_turbo_enabled() const {
    return turbo_enabled;
}

void VehicleAudioSpec::set_blowoff_enabled(bool value) {
    if (blowoff_enabled == value) {
        return;
    }
    blowoff_enabled = value;
    emit_changed();
}

bool VehicleAudioSpec::get_blowoff_enabled() const {
    return blowoff_enabled;
}

void VehicleAudioSpec::set_shift_enabled(bool value) {
    if (shift_enabled == value) {
        return;
    }
    shift_enabled = value;
    emit_changed();
}

bool VehicleAudioSpec::get_shift_enabled() const {
    return shift_enabled;
}

void VehicleAudioSpec::set_supercharger_enabled(bool value) {
    if (supercharger_enabled == value) {
        return;
    }
    supercharger_enabled = value;
    emit_changed();
}

bool VehicleAudioSpec::get_supercharger_enabled() const {
    return supercharger_enabled;
}

void VehicleAudioSpec::set_master_level(double value) {
    if (master_level == value) {
        return;
    }
    master_level = value;
    emit_changed();
}

double VehicleAudioSpec::get_master_level() const {
    return master_level;
}

void VehicleAudioSpec::set_engine_level(double value) {
    if (engine_level == value) {
        return;
    }
    engine_level = value;
    emit_changed();
}

double VehicleAudioSpec::get_engine_level() const {
    return engine_level;
}

void VehicleAudioSpec::set_transmission_level(double value) {
    if (transmission_level == value) {
        return;
    }
    transmission_level = value;
    emit_changed();
}

double VehicleAudioSpec::get_transmission_level() const {
    return transmission_level;
}

void VehicleAudioSpec::set_turbo_level(double value) {
    if (turbo_level == value) {
        return;
    }
    turbo_level = value;
    emit_changed();
}

double VehicleAudioSpec::get_turbo_level() const {
    return turbo_level;
}

void VehicleAudioSpec::set_shift_level(double value) {
    if (shift_level == value) {
        return;
    }
    shift_level = value;
    emit_changed();
}

double VehicleAudioSpec::get_shift_level() const {
    return shift_level;
}

void VehicleAudioSpec::set_duty_cycle(double value) {
    if (duty_cycle == value) {
        return;
    }
    duty_cycle = value;
    emit_changed();
}

double VehicleAudioSpec::get_duty_cycle() const {
    return duty_cycle;
}

void VehicleAudioSpec::set_pattern_strength(double value) {
    if (pattern_strength == value) {
        return;
    }
    pattern_strength = value;
    emit_changed();
}

double VehicleAudioSpec::get_pattern_strength() const {
    return pattern_strength;
}

void VehicleAudioSpec::set_rumble_resonance(double value) {
    if (rumble_resonance == value) {
        return;
    }
    rumble_resonance = value;
    emit_changed();
}

double VehicleAudioSpec::get_rumble_resonance() const {
    return rumble_resonance;
}

void VehicleAudioSpec::set_muffler_resonance_hz(double value) {
    if (muffler_resonance_hz == value) {
        return;
    }
    muffler_resonance_hz = value;
    emit_changed();
}

double VehicleAudioSpec::get_muffler_resonance_hz() const {
    return muffler_resonance_hz;
}

void VehicleAudioSpec::set_muffler_damping(double value) {
    if (muffler_damping == value) {
        return;
    }
    muffler_damping = value;
    emit_changed();
}

double VehicleAudioSpec::get_muffler_damping() const {
    return muffler_damping;
}

void VehicleAudioSpec::set_tailpipe_lowpass_hz(double value) {
    if (tailpipe_lowpass_hz == value) {
        return;
    }
    tailpipe_lowpass_hz = value;
    emit_changed();
}

double VehicleAudioSpec::get_tailpipe_lowpass_hz() const {
    return tailpipe_lowpass_hz;
}

void VehicleAudioSpec::set_exhaust_echo_strength(double value) {
    if (exhaust_echo_strength == value) {
        return;
    }
    exhaust_echo_strength = value;
    emit_changed();
}

double VehicleAudioSpec::get_exhaust_echo_strength() const {
    return exhaust_echo_strength;
}

void VehicleAudioSpec::set_throttle_intake_gain(double value) {
    if (throttle_intake_gain == value) {
        return;
    }
    throttle_intake_gain = value;
    emit_changed();
}

double VehicleAudioSpec::get_throttle_intake_gain() const {
    return throttle_intake_gain;
}

void VehicleAudioSpec::set_burble_intensity(double value) {
    if (burble_intensity == value) {
        return;
    }
    burble_intensity = value;
    emit_changed();
}

double VehicleAudioSpec::get_burble_intensity() const {
    return burble_intensity;
}

void VehicleAudioSpec::set_burble_presence(double value) {
    if (burble_presence == value) {
        return;
    }
    burble_presence = value;
    emit_changed();
}

double VehicleAudioSpec::get_burble_presence() const {
    return burble_presence;
}

void VehicleAudioSpec::set_burble_lift_duration(double value) {
    if (burble_lift_duration == value) {
        return;
    }
    burble_lift_duration = value;
    emit_changed();
}

double VehicleAudioSpec::get_burble_lift_duration() const {
    return burble_lift_duration;
}

void VehicleAudioSpec::set_turbo_base_pitch_hz(double value) {
    if (turbo_base_pitch_hz == value) {
        return;
    }
    turbo_base_pitch_hz = value;
    emit_changed();
}

double VehicleAudioSpec::get_turbo_base_pitch_hz() const {
    return turbo_base_pitch_hz;
}

void VehicleAudioSpec::set_turbo_max_pitch_hz(double value) {
    if (turbo_max_pitch_hz == value) {
        return;
    }
    turbo_max_pitch_hz = value;
    emit_changed();
}

double VehicleAudioSpec::get_turbo_max_pitch_hz() const {
    return turbo_max_pitch_hz;
}

void VehicleAudioSpec::set_turbo_induction_gain(double value) {
    if (turbo_induction_gain == value) {
        return;
    }
    turbo_induction_gain = value;
    emit_changed();
}

double VehicleAudioSpec::get_turbo_induction_gain() const {
    return turbo_induction_gain;
}

void VehicleAudioSpec::set_blowoff_gain(double value) {
    if (blowoff_gain == value) {
        return;
    }
    blowoff_gain = value;
    emit_changed();
}

double VehicleAudioSpec::get_blowoff_gain() const {
    return blowoff_gain;
}

void VehicleAudioSpec::set_blowoff_decay_rate(double value) {
    if (blowoff_decay_rate == value) {
        return;
    }
    blowoff_decay_rate = value;
    emit_changed();
}

double VehicleAudioSpec::get_blowoff_decay_rate() const {
    return blowoff_decay_rate;
}

void VehicleAudioSpec::set_supercharger_style(int64_t value) {
    if (supercharger_style == value) {
        return;
    }
    supercharger_style = value;
    emit_changed();
}

int64_t VehicleAudioSpec::get_supercharger_style() const {
    return supercharger_style;
}

void VehicleAudioSpec::set_supercharger_level(double value) {
    if (supercharger_level == value) {
        return;
    }
    supercharger_level = value;
    emit_changed();
}

double VehicleAudioSpec::get_supercharger_level() const {
    return supercharger_level;
}

void VehicleAudioSpec::set_supercharger_blowoff_enabled(bool value) {
    if (supercharger_blowoff_enabled == value) {
        return;
    }
    supercharger_blowoff_enabled = value;
    emit_changed();
}

bool VehicleAudioSpec::get_supercharger_blowoff_enabled() const {
    return supercharger_blowoff_enabled;
}

void VehicleAudioSpec::set_centrifugal_max_pitch_hz(double value) {
    if (centrifugal_max_pitch_hz == value) {
        return;
    }
    centrifugal_max_pitch_hz = value;
    emit_changed();
}

double VehicleAudioSpec::get_centrifugal_max_pitch_hz() const {
    return centrifugal_max_pitch_hz;
}

void VehicleAudioSpec::set_centrifugal_air_gain(double value) {
    if (centrifugal_air_gain == value) {
        return;
    }
    centrifugal_air_gain = value;
    emit_changed();
}

double VehicleAudioSpec::get_centrifugal_air_gain() const {
    return centrifugal_air_gain;
}

void VehicleAudioSpec::set_centrifugal_tone_gain(double value) {
    if (centrifugal_tone_gain == value) {
        return;
    }
    centrifugal_tone_gain = value;
    emit_changed();
}

double VehicleAudioSpec::get_centrifugal_tone_gain() const {
    return centrifugal_tone_gain;
}

void VehicleAudioSpec::set_centrifugal_bypass_gain(double value) {
    if (centrifugal_bypass_gain == value) {
        return;
    }
    centrifugal_bypass_gain = value;
    emit_changed();
}

double VehicleAudioSpec::get_centrifugal_bypass_gain() const {
    return centrifugal_bypass_gain;
}

void VehicleAudioSpec::set_centrifugal_air_cutoff_hz(double value) {
    if (centrifugal_air_cutoff_hz == value) {
        return;
    }
    centrifugal_air_cutoff_hz = value;
    emit_changed();
}

double VehicleAudioSpec::get_centrifugal_air_cutoff_hz() const {
    return centrifugal_air_cutoff_hz;
}

void VehicleAudioSpec::set_blowoff_tone_gain(double value) {
    if (blowoff_tone_gain == value) {
        return;
    }
    blowoff_tone_gain = value;
    emit_changed();
}

double VehicleAudioSpec::get_blowoff_tone_gain() const {
    return blowoff_tone_gain;
}

void VehicleAudioSpec::set_blowoff_flutter_depth(double value) {
    if (blowoff_flutter_depth == value) {
        return;
    }
    blowoff_flutter_depth = value;
    emit_changed();
}

double VehicleAudioSpec::get_blowoff_flutter_depth() const {
    return blowoff_flutter_depth;
}

void VehicleAudioSpec::set_supercharger_drive_ratio(double value) {
    if (supercharger_drive_ratio == value) {
        return;
    }
    supercharger_drive_ratio = value;
    emit_changed();
}

double VehicleAudioSpec::get_supercharger_drive_ratio() const {
    return supercharger_drive_ratio;
}

void VehicleAudioSpec::set_supercharger_lobes(int64_t value) {
    if (supercharger_lobes == value) {
        return;
    }
    supercharger_lobes = value;
    emit_changed();
}

int64_t VehicleAudioSpec::get_supercharger_lobes() const {
    return supercharger_lobes;
}

void VehicleAudioSpec::set_supercharger_harmonics(double value) {
    if (supercharger_harmonics == value) {
        return;
    }
    supercharger_harmonics = value;
    emit_changed();
}

double VehicleAudioSpec::get_supercharger_harmonics() const {
    return supercharger_harmonics;
}

} // namespace godot

godot::Variant godot::VehicleAudioSpec::_get_inspector_category() const {
    return Variant();
}
