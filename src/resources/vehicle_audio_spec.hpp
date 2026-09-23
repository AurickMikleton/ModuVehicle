#pragma once

#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/variant/string.hpp>
#include <godot_cpp/variant/vector3.hpp>
#include <godot_cpp/variant/packed_float32_array.hpp>
#include <godot_cpp/variant/typed_array.hpp>
#include <cstdint>
#include "engine_sound_layout.hpp"

namespace godot {

class VehicleAudioSpec : public Resource {
    GDCLASS(VehicleAudioSpec, Resource)

private:

    // Engine sound
    Ref<EngineSoundLayout> engine_layout;

    // Layers
    bool engine_enabled = true;
    bool transmission_enabled = true;
    bool burble_enabled = true;
    bool turbo_enabled = true;
    bool blowoff_enabled = true;
    bool shift_enabled = true;
    bool supercharger_enabled = false;
    double master_level = 0.72;
    double engine_level = 0.72;
    double transmission_level = 0.28;
    double turbo_level = 0.30;
    double shift_level = 1.0;

    // Exhaust and intake
    double duty_cycle = 0.30;
    double pattern_strength = 0.65;
    double rumble_resonance = 0.32;
    double muffler_resonance_hz = 180.0;
    double muffler_damping = 0.15;
    double tailpipe_lowpass_hz = 6000.0;
    double exhaust_echo_strength = 0.15;
    double throttle_intake_gain = 0.45;
    double burble_intensity = 0.82;
    // Dry transient mix after the muffler; preserves the short pop attack.
    double burble_presence = 0.65;
    double burble_lift_duration = 0.9;

    // Turbo and blow-off
    double turbo_base_pitch_hz = 620.0;
    double turbo_max_pitch_hz = 8400.0;
    double turbo_induction_gain = 0.24;
    double blowoff_gain = 0.58;
    // Smaller numbers give a longer pressure release.
    double blowoff_decay_rate = 5.2;

    // Supercharger
    int64_t supercharger_style = 0;
    double supercharger_level = 0.35;
    bool supercharger_blowoff_enabled = true;
    double centrifugal_max_pitch_hz = 7200.0;
    double centrifugal_air_gain = 0.35;
    // Independent air/whistle balance; bypass airflow persists with belt speed on lift.
    double centrifugal_tone_gain = 0.65;
    double centrifugal_bypass_gain = 0.0;
    double centrifugal_air_cutoff_hz = 6500.0;
    double blowoff_tone_gain = 0.20;
    double blowoff_flutter_depth = 0.32;
    // Tone frequency = engine revolutions per second * pulley ratio * lobe count.
    double supercharger_drive_ratio = 2.0;
    int64_t supercharger_lobes = 6;
    double supercharger_harmonics = 0.35;

protected:
    static void _bind_methods();
    Variant _get_inspector_category() const;

public:
    VehicleAudioSpec();

    void set_engine_layout(const Ref<EngineSoundLayout> &value);
    Ref<EngineSoundLayout> get_engine_layout() const;

    void set_engine_enabled(bool value);
    bool get_engine_enabled() const;

    void set_transmission_enabled(bool value);
    bool get_transmission_enabled() const;

    void set_burble_enabled(bool value);
    bool get_burble_enabled() const;

    void set_turbo_enabled(bool value);
    bool get_turbo_enabled() const;

    void set_blowoff_enabled(bool value);
    bool get_blowoff_enabled() const;

    void set_shift_enabled(bool value);
    bool get_shift_enabled() const;

    void set_supercharger_enabled(bool value);
    bool get_supercharger_enabled() const;

    void set_master_level(double value);
    double get_master_level() const;

    void set_engine_level(double value);
    double get_engine_level() const;

    void set_transmission_level(double value);
    double get_transmission_level() const;

    void set_turbo_level(double value);
    double get_turbo_level() const;

    void set_shift_level(double value);
    double get_shift_level() const;

    void set_duty_cycle(double value);
    double get_duty_cycle() const;

    void set_pattern_strength(double value);
    double get_pattern_strength() const;

    void set_rumble_resonance(double value);
    double get_rumble_resonance() const;

    void set_muffler_resonance_hz(double value);
    double get_muffler_resonance_hz() const;

    void set_muffler_damping(double value);
    double get_muffler_damping() const;

    void set_tailpipe_lowpass_hz(double value);
    double get_tailpipe_lowpass_hz() const;

    void set_exhaust_echo_strength(double value);
    double get_exhaust_echo_strength() const;

    void set_throttle_intake_gain(double value);
    double get_throttle_intake_gain() const;

    void set_burble_intensity(double value);
    double get_burble_intensity() const;

    void set_burble_presence(double value);
    double get_burble_presence() const;

    void set_burble_lift_duration(double value);
    double get_burble_lift_duration() const;

    void set_turbo_base_pitch_hz(double value);
    double get_turbo_base_pitch_hz() const;

    void set_turbo_max_pitch_hz(double value);
    double get_turbo_max_pitch_hz() const;

    void set_turbo_induction_gain(double value);
    double get_turbo_induction_gain() const;

    void set_blowoff_gain(double value);
    double get_blowoff_gain() const;

    void set_blowoff_decay_rate(double value);
    double get_blowoff_decay_rate() const;

    void set_supercharger_style(int64_t value);
    int64_t get_supercharger_style() const;

    void set_supercharger_level(double value);
    double get_supercharger_level() const;

    void set_supercharger_blowoff_enabled(bool value);
    bool get_supercharger_blowoff_enabled() const;

    void set_centrifugal_max_pitch_hz(double value);
    double get_centrifugal_max_pitch_hz() const;

    void set_centrifugal_air_gain(double value);
    double get_centrifugal_air_gain() const;

    void set_centrifugal_tone_gain(double value);
    double get_centrifugal_tone_gain() const;

    void set_centrifugal_bypass_gain(double value);
    double get_centrifugal_bypass_gain() const;

    void set_centrifugal_air_cutoff_hz(double value);
    double get_centrifugal_air_cutoff_hz() const;

    void set_blowoff_tone_gain(double value);
    double get_blowoff_tone_gain() const;

    void set_blowoff_flutter_depth(double value);
    double get_blowoff_flutter_depth() const;

    void set_supercharger_drive_ratio(double value);
    double get_supercharger_drive_ratio() const;

    void set_supercharger_lobes(int64_t value);
    int64_t get_supercharger_lobes() const;

    void set_supercharger_harmonics(double value);
    double get_supercharger_harmonics() const;

};

} // namespace godot
