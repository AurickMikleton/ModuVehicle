#include "exhaust.hpp"

using namespace godot;

#include "godot_cpp/classes/engine.hpp"

MoVeExhaust::MoVeExhaust() {
	firing_pattern = Array::make(1.0, 0.82, 1.28, 0.96);
}

void MoVeExhaust::init() {
	if (get_stream().is_null()) {
		ERR_PRINT("EngineAudio requires an AudioStreamGenerator.");
		return;
	}

	play();
	playback = get_stream_playback();
	if (playback.is_null()) {
		ERR_PRINT("Failed to get AudioStreamPlayback.");
		return;
	}

	//sample_hz = get_stream()->get_mix_rate();
	init_exhaust_dsp(sample_hz);
}


/* ================= External API ================= */

void MoVeExhaust::set_rpm(float value) {
	rpm = value;
	pulse_hz = (rpm / 60.0f) * (cylinders / (strokes / 2.0f));
}

void MoVeExhaust::set_throttle(float value) {
	throttle = Math::clamp(value, 0.0f, 1.0f);
}

/* ================= DSP Core ================= */

void MoVeExhaust::_fill_buffer() {
	if (!playback.is_valid()) return;

	int frames = playback->get_frames_available();
	if (frames <= 0) return;

	static double t = 0.0;
	double freq = 220.0;

	for (int i = 0; i < frames; i++) {
		double sample = Math::sin(Math_TAU * freq * t) * 0.2;
		t += 1.0 / sample_hz;

		playback->push_frame(Vector2(sample, sample));
	}
}

void MoVeExhaust::fill_buffer() {
    if (!playback.is_valid()) return;

	int frames = playback->get_frames_available();
	if (frames <= 0) return;

	PackedFloat32Array buffer;
	buffer.resize(frames);

	for (int i = 0; i < frames; i++) {
		float pattern = firing_pattern[firing_step];
		firing_step = (firing_step + 1) % firing_pattern.size();

		float phase_inc =
			(pulse_hz / sample_hz) *
			Math::lerp(1.0f, pattern, pattern_strength);

		// Pulse wave
		float pulse = 0.0f;
		for (int h = 1; h <= wave_quality; h++) {
			float sharp = 1.0f + throttle * throttle_attack_sharpness;
			pulse += (Math::sin(Math_PI * h * duty_cycle * sharp) / h)
			       * Math::cos(Math_TAU * h * phase);
		}
		pulse = (pulse * (4.0f / Math_PI)) + (2.0f * duty_cycle - 1.0f);

		float noise =
			UtilityFunctions::randf() * 0.6f +
			UtilityFunctions::randf() * 0.3f +
			UtilityFunctions::randf() * 0.1f;

		float base_engine = Math::max(0.0f, pulse) * noise;
		float intake = throttle * throttle_intake_gain *
			(UtilityFunctions::randf() * 0.6f + 0.4f);

		float rumble = Math::sin(rumble_lfo_phase) * rumble_resonance;
		rumble_lfo_phase =
			Math::fmod(rumble_lfo_phase + 0.002 + rpm / 200000.0, Math_TAU);

		float raw = base_engine + rumble + intake;

		float vol = starting_volume +
			(rpm / max_rpm) * (1.0f - starting_volume);
		vol += throttle * throttle_volume_gain;
		raw *= vol;

		raw = apply_burbles(raw);
		raw = exhaust_dsp(raw);

		buffer[i] = raw;
		phase = Math::fmod(phase + phase_inc, 1.0f);
	}

	PackedFloat32Array filtered = lowpass(buffer);
	for (int i = 0; i < filtered.size(); i++) {
		playback->push_frame(Vector2(filtered[i], filtered[i]));
	}
}

PackedFloat32Array MoVeExhaust::lowpass(const PackedFloat32Array &input) {
	PackedFloat32Array output;
	output.resize(input.size());

	float rpm_ratio = Math::clamp(
		(rpm - idle_rpm) / (max_rpm - idle_rpm),
		0.0f, 1.0f
	);

	float cutoff = Math::lerp(lowpass_floor, lowpass_ceiling, rpm_ratio);
	cutoff += throttle * throttle_brightness_boost;
	cutoff = Math::min(cutoff, sample_hz * 0.45f);

	float t = Math::tan(Math_PI * cutoff / sample_hz);
	float a1 = (t - 1.0f) / (t + 1.0f);

	for (int i = 0; i < input.size(); i++) {
		float x = input[i];
		float ap = a1 * x + ap_dn1;
		ap_dn1 = x - a1 * ap;
		output[i] = 0.5f * (x + ap);
	}
	return output;
}

float MoVeExhaust::exhaust_dsp(float input_sample) {
	float k = (Math_TAU * muff_resonance) / sample_hz;
	float d = muff_damping;

	muff_vel += (input_sample - muff_pos) * k;
	muff_vel *= (1.0f - d);
	muff_pos += muff_vel;

	float resonated = muff_pos;

	float rc = 1.0f / (Math_TAU * tailpipe_lp);
	float alpha = Math::clamp(
		sample_hz * rc / (sample_hz * rc + 1.0f),
		0.0f, 1.0f
	);

	float low_passed = lp_prev + alpha * (resonated - lp_prev);
	lp_prev = low_passed;

	float delayed = echo_buffer[echo_index];
	echo_buffer[echo_index] = low_passed;
	echo_index = (echo_index + 1) % echo_buffer.size();

	return low_passed + delayed * exhaust_echo_strength;
}

float MoVeExhaust::apply_burbles(float raw) {
	if (enable_burble && throttle < 0.1f && rpm > idle_rpm + 400.0f) {
		if (!burble_active) {
			burble_active = true;
			burble_timer = UtilityFunctions::randf_range(0.05f, 0.20f);
			burble_gap = 0.0f;
		}
	} else {
		burble_active = false;
	}

	if (!burble_active) return raw;

	burble_timer -= 1.0f / sample_hz;
	if (burble_timer <= 0.0f) {
		burble_active = false;
		return raw;
	}

	burble_gap -= 1.0f / sample_hz;
	if (burble_gap <= 0.0f) {
		float pop =
			UtilityFunctions::randf_range(-1.0f, 1.0f) *
			burble_intensity *
			(rpm / max_rpm + 0.4f);

		pop *= pop * pop;
		raw += pop;

		burble_gap = UtilityFunctions::randf_range(0.002f, 0.015f);
	}

	return raw;
}

void MoVeExhaust::init_exhaust_dsp(float sample_rate) {
	int len = Math::max(1, int(exhaust_echo_delay * sample_rate));
	echo_buffer.resize(len);
	for (int i = 0; i < len; i++) {
		echo_buffer[i] = 0.0f;
	}
	echo_index = 0;
}

void MoVeExhaust::set_engine(Ref<MoVeEngine> value) {m_engine = value;}
Ref<MoVeEngine> MoVeExhaust::get_engine() const {return m_engine;}

void MoVeExhaust::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_engine", "value"), &MoVeExhaust::set_engine);
    ClassDB::bind_method(D_METHOD("get_engine"), &MoVeExhaust::get_engine);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "engine", PROPERTY_HINT_RESOURCE_TYPE, "MoVeEngine"), "set_engine", "get_engine");

	ClassDB::bind_method(D_METHOD("set_rpm", "rpm"), &MoVeExhaust::set_rpm);
	ClassDB::bind_method(D_METHOD("set_throttle", "throttle"), &MoVeExhaust::set_throttle);
    ClassDB::bind_method(D_METHOD("fill_buffer"), &MoVeExhaust::fill_buffer);
    ClassDB::bind_method(D_METHOD("init"), &MoVeExhaust::init);

	// ADD_GROUP("Engine", "");
	// ADD_PROPERTY(PropertyInfo(Variant::INT, "cylinders"), "", "cylinders");
	// ADD_PROPERTY(PropertyInfo(Variant::INT, "strokes"), "", "strokes");
	// ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "max_rpm"), "", "max_rpm");
	// ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "idle_rpm"), "", "idle_rpm");

	// ADD_GROUP("Sound Shape", "");
	// ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "firing_pattern"), "", "firing_pattern");
	// ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "duty_cycle"), "", "duty_cycle");
	// ADD_PROPERTY(PropertyInfo(Variant::INT, "wave_quality"), "", "wave_quality");
	// ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "starting_volume"), "", "starting_volume");
	// ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "rumble_resonance"), "", "rumble_resonance");
	// ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "pattern_strength"), "", "pattern_strength");
	// ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "lowpass_floor"), "", "lowpass_floor");
	// ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "lowpass_ceiling"), "", "lowpass_ceiling");

	// ADD_GROUP("Throttle", "");
	// ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "throttle_intake_gain"), "", "throttle_intake_gain");
	// ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "throttle_attack_sharpness"), "", "throttle_attack_sharpness");
	// ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "throttle_brightness_boost"), "", "throttle_brightness_boost");
	// ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "throttle_volume_gain"), "", "throttle_volume_gain");

	// ADD_GROUP("Muffler", "");
	// ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "muff_resonance"), "", "muff_resonance");
	// ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "muff_damping"), "", "muff_damping");
	// ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "tailpipe_lp"), "", "tailpipe_lp");
	// ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "exhaust_echo_strength"), "", "exhaust_echo_strength");
	// ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "exhaust_echo_delay"), "", "exhaust_echo_delay");

	// ADD_GROUP("Burble", "");
	// ADD_PROPERTY(PropertyInfo(Variant::BOOL, "enable_burble"), "", "enable_burble");
	// ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "burble_intensity"), "", "burble_intensity");
}