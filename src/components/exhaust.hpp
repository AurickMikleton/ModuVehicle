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
	Ref<AudioStreamGeneratorPlayback> playback;
	float sample_hz = 44100.0f;

	/* ===== Runtime state ===== */
	float throttle = 0.0f;

	float rpm = 0.0f;
	float pulse_hz = 0.0f;
	float phase = 0.0f;
	float ap_dn1 = 0.0f;
	float rumble_lfo_phase = 0.0f;

	int firing_step = 0;

	/* ===== Muffler / exhaust ===== */
	float muff_vel = 0.0f;
	float muff_pos = 0.0f;
	float lp_prev = 0.0f;

	PackedFloat32Array echo_buffer;
	int echo_index = 0;

	/* ===== Burble ===== */
	bool burble_active = false;
	float burble_timer = 0.1f;
	float burble_gap = 0.2f;

    bool was_playing = false;

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

	/* ===== Exports ===== */

	// Engine
	int cylinders = 4;
	int strokes = 4;
	float max_rpm = 7000.0f;
	float idle_rpm = 750.0f;

	// Sound shape
	Array firing_pattern;
	float duty_cycle = 0.30f;
	int wave_quality = 12;
	float starting_volume = 0.12f;
	float rumble_resonance = 0.32f;
	float pattern_strength = 0.65f;
	float lowpass_floor = 2000.0f;
	float lowpass_ceiling = 12000.0f;

	// Throttle
	float throttle_intake_gain = 0.45f;
	float throttle_attack_sharpness = 0.35f;
	float throttle_brightness_boost = 5000.0f;
	float throttle_volume_gain = 0.4f;

	// Muffler
	float muff_resonance = 180.0f;
	float muff_damping = 0.15f;
	float tailpipe_lp = 6000.0f;
	float exhaust_echo_strength = 0.15f;
	float exhaust_echo_delay = 0.012f;

	// Burble
	bool enable_burble = true;
	float burble_intensity = 1.5f;

    void set_engine(Ref<MoVeEngine> value); Ref<MoVeEngine> get_engine() const;
};