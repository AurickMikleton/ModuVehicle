#pragma once

#include "godot_cpp/classes/audio_stream_player.hpp"
#include "godot_cpp/variant/packed_float32_array.hpp"
#include "godot_cpp/variant/vector2.hpp"
#include "godot_cpp/core/math.hpp"

#include "godot_cpp/classes/audio_stream_generator.hpp"
#include "godot_cpp/classes/audio_stream_generator_playback.hpp"

#include "engine.hpp"

using namespace godot;

class MoVeExhaust : public AudioStreamPlayer {
	GDCLASS(MoVeExhaust, AudioStreamPlayer);

private:
    Ref<MoVeEngine> m_engine;
	Ref<AudioStreamGeneratorPlayback> m_playback;
	float m_sample_hz = 44100.0f;

	/* ===== Runtime state ===== */
	float m_throttle = 0.0f;

	float m_rpm = 0.0f;
	float m_pulse_hz = 0.0f;
	float m_phase = 0.0f;
	float m_ap_dn1 = 0.0f;
	float m_rumble_lfo_phase = 0.0f;

	int m_firing_step = 0;
    
	// Muffler / Exhaust
	float m_muff_vel = 0.0f;
	float m_muff_pos = 0.0f;
	float m_lp_prev = 0.0f;

	PackedFloat32Array echo_buffer;
	int m_echo_index = 0;

	// Burble
	bool m_burble_active = false;
	float m_burble_timer = 0.1f;
	float m_burble_gap = 0.2f;

    bool m_was_playing = false;

    /* ===== Exports ===== */

	// Engine
	int m_cylinders = 4;
	int m_strokes = 4;
	float m_max_rpm = 7000.0f;
	float m_idle_rpm = 750.0f;

	// Sound shape
	Array m_firing_pattern;
	float m_duty_cycle = 0.30f;
	int m_wave_quality = 12;
	float m_starting_volume = 0.12f;
	float m_rumble_resonance = 0.32f;
	float m_pattern_strength = 0.65f;
	float m_lowpass_floor = 2000.0f;
	float m_lowpass_ceiling = 12000.0f;

	// Throttle
	float m_throttle_intake_gain = 0.45f;
	float m_throttle_attack_sharpness = 0.35f;
	float m_throttle_brightness_boost = 5000.0f;
	float m_throttle_volume_gain = 0.4f;

	// Muffler
	float m_muff_resonance = 180.0f;
	float m_muff_damping = 0.15f;
	float m_tailpipe_lp = 6000.0f;
	float m_exhaust_echo_strength = 0.15f;
	float m_exhaust_echo_delay = 0.012f;

	// Burble
	bool m_enable_burble = true;
	float m_burble_intensity = 1.5f;

protected:
	static void _bind_methods();

public:
	MoVeExhaust();

	void init();
	//void _physics_process(double delta) override;

	/* ===== External API ===== */
	void set_rpm(float value);
	void set_throttle(float value);

	/* ===== DSP ===== */
	void fill_buffer();
    void _fill_buffer();
	PackedFloat32Array lowpass(const PackedFloat32Array &input);
	float exhaust_dsp(float input_sample);
	float apply_burbles(float raw);
	void init_exhaust_dsp(float sample_rate);

    void set_engine(Ref<MoVeEngine> value); Ref<MoVeEngine> get_engine() const;
        // Engine
    void set_cylinders(int value);
    int get_cylinders() const;

    void set_strokes(int value);
    int get_strokes() const;

    void set_max_rpm(float value);
    float get_max_rpm() const;

    void set_idle_rpm(float value);
    float get_idle_rpm() const;

    // Sound shape
    void set_firing_pattern(const Array &value);
    Array get_firing_pattern() const;

    void set_duty_cycle(float value);
    float get_duty_cycle() const;

    void set_wave_quality(int value);
    int get_wave_quality() const;

    void set_starting_volume(float value);
    float get_starting_volume() const;

    void set_rumble_resonance(float value);
    float get_rumble_resonance() const;

    void set_pattern_strength(float value);
    float get_pattern_strength() const;

    void set_lowpass_floor(float value);
    float get_lowpass_floor() const;

    void set_lowpass_ceiling(float value);
    float get_lowpass_ceiling() const;

    // Throttle
    void set_throttle_intake_gain(float value);
    float get_throttle_intake_gain() const;

    void set_throttle_attack_sharpness(float value);
    float get_throttle_attack_sharpness() const;

    void set_throttle_brightness_boost(float value);
    float get_throttle_brightness_boost() const;

    void set_throttle_volume_gain(float value);
    float get_throttle_volume_gain() const;

    // Muffler
    void set_muff_resonance(float value);
    float get_muff_resonance() const;

    void set_muff_damping(float value);
    float get_muff_damping() const;

    void set_tailpipe_lp(float value);
    float get_tailpipe_lp() const;

    void set_exhaust_echo_strength(float value);
    float get_exhaust_echo_strength() const;

    void set_exhaust_echo_delay(float value);
    float get_exhaust_echo_delay() const;

    // Burble
    void set_enable_burble(bool value);
    bool get_enable_burble() const;

    void set_burble_intensity(float value);
    float get_burble_intensity() const;
};