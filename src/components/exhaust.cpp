#include "exhaust.hpp"

using namespace godot;

#include "godot_cpp/classes/engine.hpp"

MoVeExhaust::MoVeExhaust() {
	m_firing_pattern = Array::make(1.0, 0.82, 1.28, 0.96);
}

void MoVeExhaust::init() {
	if (get_stream().is_null()) {
		ERR_PRINT("EngineAudio requires an AudioStreamGenerator.");
		return;
	}

	play();
	m_playback = get_stream_playback();
	if (m_playback.is_null()) {
		ERR_PRINT("Failed to get AudioStreamPlayback.");
		return;
	}

	//sample_hz = get_stream()->get_mix_rate();
	init_exhaust_dsp(m_sample_hz);
}

void MoVeExhaust::set_rpm(float value) {
	m_rpm = value;
	m_pulse_hz = (m_rpm / 60.0f) * (m_cylinders / (m_strokes / 2.0f));
}

void MoVeExhaust::set_throttle(float value) {
	m_throttle = Math::clamp(value, 0.0f, 1.0f);
}

/* ================= DSP Core ================= */

void MoVeExhaust::fill_buffer() {
    if (!m_playback.is_valid()) return;

	int frames = m_playback->get_frames_available();
	if (frames <= 0) return;

	PackedFloat32Array buffer;
	buffer.resize(frames);

	for (int i = 0; i < frames; i++) {
		float pattern = m_firing_pattern[m_firing_step];
		m_firing_step = (m_firing_step + 1) % m_firing_pattern.size();

		float phase_inc =
			(m_pulse_hz / m_sample_hz) *
			Math::lerp(1.0f, pattern, m_pattern_strength);

		// Pulse wave
		float pulse = 0.0f;
		for (int h = 1; h <= m_wave_quality; h++) {
			float sharp = 1.0f + m_throttle * m_throttle_attack_sharpness;
			pulse += (Math::sin(Math_PI * h * m_duty_cycle * sharp) / h)
			       * Math::cos(Math_TAU * h * m_phase);
		}
		pulse = (pulse * (4.0f / Math_PI)) + (2.0f * m_duty_cycle - 1.0f);

		float noise =
			UtilityFunctions::randf() * 0.6f +
			UtilityFunctions::randf() * 0.3f +
			UtilityFunctions::randf() * 0.1f;

		float base_engine = Math::max(0.0f, pulse) * noise;
		float intake = m_throttle * m_throttle_intake_gain *
			(UtilityFunctions::randf() * 0.6f + 0.4f);

		float rumble = Math::sin(m_rumble_lfo_phase) * m_rumble_resonance;
		m_rumble_lfo_phase =
			Math::fmod(m_rumble_lfo_phase + 0.002 + m_rpm / 200000.0, Math_TAU);

		float raw = base_engine + rumble + intake;

		float vol = m_starting_volume +
			(m_rpm / m_max_rpm) * (1.0f - m_starting_volume);
		vol += m_throttle * m_throttle_volume_gain;
		raw *= vol;

		raw = apply_burbles(raw);
		raw = exhaust_dsp(raw);

		buffer[i] = raw;
		m_phase = Math::fmod(m_phase + phase_inc, 1.0f);
	}

	PackedFloat32Array filtered = lowpass(buffer);
	for (int i = 0; i < filtered.size(); i++) {
		m_playback->push_frame(Vector2(filtered[i], filtered[i]));
	}
}

PackedFloat32Array MoVeExhaust::lowpass(const PackedFloat32Array &input) {
	PackedFloat32Array output;
	output.resize(input.size());

	float rpm_ratio = Math::clamp(
		(m_rpm - m_idle_rpm) / (m_max_rpm - m_idle_rpm),
		0.0f, 1.0f
	);

	float cutoff = Math::lerp(m_lowpass_floor, m_lowpass_ceiling, rpm_ratio);
	cutoff += m_throttle * m_throttle_brightness_boost;
	cutoff = Math::min(cutoff, m_sample_hz * 0.45f);

	float t = Math::tan(Math_PI * cutoff / m_sample_hz);
	float a1 = (t - 1.0f) / (t + 1.0f);

	for (int i = 0; i < input.size(); i++) {
		float x = input[i];
		float ap = a1 * x + m_ap_dn1;
		m_ap_dn1 = x - a1 * ap;
		output[i] = 0.5f * (x + ap);
	}
	return output;
}

float MoVeExhaust::exhaust_dsp(float input_sample) {
	float k = (Math_TAU * m_muff_resonance) / m_sample_hz;
	float d = m_muff_damping;

	m_muff_vel += (input_sample - m_muff_pos) * k;
	m_muff_vel *= (1.0f - d);
	m_muff_pos += m_muff_vel;

	float resonated = m_muff_pos;

	float rc = 1.0f / (Math_TAU * m_tailpipe_lp);
	float alpha = Math::clamp(
		m_sample_hz * rc / (m_sample_hz * rc + 1.0f),
		0.0f, 1.0f
	);

	float low_passed = m_lp_prev + alpha * (resonated - m_lp_prev);
	m_lp_prev = low_passed;

	float delayed = echo_buffer[m_echo_index];
	echo_buffer[m_echo_index] = low_passed;
	m_echo_index = (m_echo_index + 1) % echo_buffer.size();

	return low_passed + delayed * m_exhaust_echo_strength;
}

float MoVeExhaust::apply_burbles(float raw) {
	if (m_enable_burble && m_throttle < 0.1f && m_rpm > m_idle_rpm + 400.0f) {
		if (!m_burble_active) {
			m_burble_active = true;
			m_burble_timer = UtilityFunctions::randf_range(0.05f, 0.20f);
			m_burble_gap = 0.0f;
		}
	} else {
		m_burble_active = false;
	}

	if (!m_burble_active) return raw;

	m_burble_timer -= 1.0f / m_sample_hz;
	if (m_burble_timer <= 0.0f) {
		m_burble_active = false;
		return raw;
	}

	m_burble_gap -= 1.0f / m_sample_hz;
	if (m_burble_gap <= 0.0f) {
		float pop =
			UtilityFunctions::randf_range(-1.0f, 1.0f) *
			m_burble_intensity *
			(m_rpm / m_max_rpm + 0.4f);

		pop *= pop * pop;
		raw += pop;

		m_burble_gap = UtilityFunctions::randf_range(0.002f, 0.015f);
	}

	return raw;
}

void MoVeExhaust::init_exhaust_dsp(float sample_rate) {
	int len = Math::max(1, int(m_exhaust_echo_delay * sample_rate));
	echo_buffer.resize(len);
	for (int i = 0; i < len; i++) {
		echo_buffer[i] = 0.0f;
	}
	m_echo_index = 0;
}

void MoVeExhaust::set_engine(Ref<MoVeEngine> value) {m_engine = value;}
Ref<MoVeEngine> MoVeExhaust::get_engine() const {return m_engine;}

void MoVeExhaust::set_cylinders(int value) { m_cylinders = value; }
int MoVeExhaust::get_cylinders() const { return m_cylinders; }

void MoVeExhaust::set_strokes(int value) { m_strokes = value; }
int MoVeExhaust::get_strokes() const { return m_strokes; }

void MoVeExhaust::set_max_rpm(float value) { m_max_rpm = value; }
float MoVeExhaust::get_max_rpm() const { return m_max_rpm; }

void MoVeExhaust::set_idle_rpm(float value) { m_idle_rpm = value; }
float MoVeExhaust::get_idle_rpm() const { return m_idle_rpm; }

// --- Sound Shape ---
void MoVeExhaust::set_firing_pattern(const Array &value) { m_firing_pattern = value; }
Array MoVeExhaust::get_firing_pattern() const { return m_firing_pattern; }

void MoVeExhaust::set_duty_cycle(float value) { m_duty_cycle = value; }
float MoVeExhaust::get_duty_cycle() const { return m_duty_cycle; }

void MoVeExhaust::set_wave_quality(int value) { m_wave_quality = value; }
int MoVeExhaust::get_wave_quality() const { return m_wave_quality; }

void MoVeExhaust::set_starting_volume(float value) { m_starting_volume = value; }
float MoVeExhaust::get_starting_volume() const { return m_starting_volume; }

void MoVeExhaust::set_rumble_resonance(float value) { m_rumble_resonance = value; }
float MoVeExhaust::get_rumble_resonance() const { return m_rumble_resonance; }

void MoVeExhaust::set_pattern_strength(float value) { m_pattern_strength = value; }
float MoVeExhaust::get_pattern_strength() const { return m_pattern_strength; }

void MoVeExhaust::set_lowpass_floor(float value) { m_lowpass_floor = value; }
float MoVeExhaust::get_lowpass_floor() const { return m_lowpass_floor; }

void MoVeExhaust::set_lowpass_ceiling(float value) { m_lowpass_ceiling = value; }
float MoVeExhaust::get_lowpass_ceiling() const { return m_lowpass_ceiling; }

// --- Throttle ---
void MoVeExhaust::set_throttle_intake_gain(float value) { m_throttle_intake_gain = value; }
float MoVeExhaust::get_throttle_intake_gain() const { return m_throttle_intake_gain; }

void MoVeExhaust::set_throttle_attack_sharpness(float value) { m_throttle_attack_sharpness = value; }
float MoVeExhaust::get_throttle_attack_sharpness() const { return m_throttle_attack_sharpness; }

void MoVeExhaust::set_throttle_brightness_boost(float value) { m_throttle_brightness_boost = value; }
float MoVeExhaust::get_throttle_brightness_boost() const { return m_throttle_brightness_boost; }

void MoVeExhaust::set_throttle_volume_gain(float value) { m_throttle_volume_gain = value; }
float MoVeExhaust::get_throttle_volume_gain() const { return m_throttle_volume_gain; }

// --- Muffler ---
void MoVeExhaust::set_muff_resonance(float value) { m_muff_resonance = value; }
float MoVeExhaust::get_muff_resonance() const { return m_muff_resonance; }

void MoVeExhaust::set_muff_damping(float value) { m_muff_damping = value; }
float MoVeExhaust::get_muff_damping() const { return m_muff_damping; }

void MoVeExhaust::set_tailpipe_lp(float value) { m_tailpipe_lp = value; }
float MoVeExhaust::get_tailpipe_lp() const { return m_tailpipe_lp; }

void MoVeExhaust::set_exhaust_echo_strength(float value) { m_exhaust_echo_strength = value; }
float MoVeExhaust::get_exhaust_echo_strength() const { return m_exhaust_echo_strength; }

void MoVeExhaust::set_exhaust_echo_delay(float value) { m_exhaust_echo_delay = value; }
float MoVeExhaust::get_exhaust_echo_delay() const { return m_exhaust_echo_delay; }

// --- Burble ---
void MoVeExhaust::set_enable_burble(bool value) { m_enable_burble = value; }
bool MoVeExhaust::get_enable_burble() const { return m_enable_burble; }

void MoVeExhaust::set_burble_intensity(float value) { m_burble_intensity = value; }
float MoVeExhaust::get_burble_intensity() const { return m_burble_intensity; }

void MoVeExhaust::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_engine", "value"), &MoVeExhaust::set_engine);
    ClassDB::bind_method(D_METHOD("get_engine"), &MoVeExhaust::get_engine);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "engine", PROPERTY_HINT_RESOURCE_TYPE, "MoVeEngine"), "set_engine", "get_engine");

	ClassDB::bind_method(D_METHOD("set_rpm", "rpm"), &MoVeExhaust::set_rpm);
	ClassDB::bind_method(D_METHOD("set_throttle", "throttle"), &MoVeExhaust::set_throttle);
    ClassDB::bind_method(D_METHOD("fill_buffer"), &MoVeExhaust::fill_buffer);
    ClassDB::bind_method(D_METHOD("init"), &MoVeExhaust::init);

     // Engine
    ClassDB::bind_method(D_METHOD("set_cylinders", "value"), &MoVeExhaust::set_cylinders);
    ClassDB::bind_method(D_METHOD("get_cylinders"), &MoVeExhaust::get_cylinders);
    ClassDB::bind_method(D_METHOD("set_strokes", "value"), &MoVeExhaust::set_strokes);
    ClassDB::bind_method(D_METHOD("get_strokes"), &MoVeExhaust::get_strokes);
    ClassDB::bind_method(D_METHOD("set_max_rpm", "value"), &MoVeExhaust::set_max_rpm);
    ClassDB::bind_method(D_METHOD("get_max_rpm"), &MoVeExhaust::get_max_rpm);
    ClassDB::bind_method(D_METHOD("set_idle_rpm", "value"), &MoVeExhaust::set_idle_rpm);
    ClassDB::bind_method(D_METHOD("get_idle_rpm"), &MoVeExhaust::get_idle_rpm);
    // Sound Shape
    ClassDB::bind_method(D_METHOD("set_firing_pattern", "value"), &MoVeExhaust::set_firing_pattern);
    ClassDB::bind_method(D_METHOD("get_firing_pattern"), &MoVeExhaust::get_firing_pattern);
    ClassDB::bind_method(D_METHOD("set_duty_cycle", "value"), &MoVeExhaust::set_duty_cycle);
    ClassDB::bind_method(D_METHOD("get_duty_cycle"), &MoVeExhaust::get_duty_cycle);
    ClassDB::bind_method(D_METHOD("set_wave_quality", "value"), &MoVeExhaust::set_wave_quality);
    ClassDB::bind_method(D_METHOD("get_wave_quality"), &MoVeExhaust::get_wave_quality);
    ClassDB::bind_method(D_METHOD("set_starting_volume", "value"), &MoVeExhaust::set_starting_volume);
    ClassDB::bind_method(D_METHOD("get_starting_volume"), &MoVeExhaust::get_starting_volume);
    ClassDB::bind_method(D_METHOD("set_rumble_resonance", "value"), &MoVeExhaust::set_rumble_resonance);
    ClassDB::bind_method(D_METHOD("get_rumble_resonance"), &MoVeExhaust::get_rumble_resonance);
    ClassDB::bind_method(D_METHOD("set_pattern_strength", "value"), &MoVeExhaust::set_pattern_strength);
    ClassDB::bind_method(D_METHOD("get_pattern_strength"), &MoVeExhaust::get_pattern_strength);
    ClassDB::bind_method(D_METHOD("set_lowpass_floor", "value"), &MoVeExhaust::set_lowpass_floor);
    ClassDB::bind_method(D_METHOD("get_lowpass_floor"), &MoVeExhaust::get_lowpass_floor);
    ClassDB::bind_method(D_METHOD("set_lowpass_ceiling", "value"), &MoVeExhaust::set_lowpass_ceiling);
    ClassDB::bind_method(D_METHOD("get_lowpass_ceiling"), &MoVeExhaust::get_lowpass_ceiling);
    // Throttle
    ClassDB::bind_method(D_METHOD("set_throttle_intake_gain", "value"), &MoVeExhaust::set_throttle_intake_gain);
    ClassDB::bind_method(D_METHOD("get_throttle_intake_gain"), &MoVeExhaust::get_throttle_intake_gain);
    ClassDB::bind_method(D_METHOD("set_throttle_attack_sharpness", "value"), &MoVeExhaust::set_throttle_attack_sharpness);
    ClassDB::bind_method(D_METHOD("get_throttle_attack_sharpness"), &MoVeExhaust::get_throttle_attack_sharpness);
    ClassDB::bind_method(D_METHOD("set_throttle_brightness_boost", "value"), &MoVeExhaust::set_throttle_brightness_boost);
    ClassDB::bind_method(D_METHOD("get_throttle_brightness_boost"), &MoVeExhaust::get_throttle_brightness_boost);
    ClassDB::bind_method(D_METHOD("set_throttle_volume_gain", "value"), &MoVeExhaust::set_throttle_volume_gain);
    ClassDB::bind_method(D_METHOD("get_throttle_volume_gain"), &MoVeExhaust::get_throttle_volume_gain);
    // Muffler
    ClassDB::bind_method(D_METHOD("set_muff_resonance", "value"), &MoVeExhaust::set_muff_resonance);
    ClassDB::bind_method(D_METHOD("get_muff_resonance"), &MoVeExhaust::get_muff_resonance);
    ClassDB::bind_method(D_METHOD("set_muff_damping", "value"), &MoVeExhaust::set_muff_damping);
    ClassDB::bind_method(D_METHOD("get_muff_damping"), &MoVeExhaust::get_muff_damping);
    ClassDB::bind_method(D_METHOD("set_tailpipe_lp", "value"), &MoVeExhaust::set_tailpipe_lp);
    ClassDB::bind_method(D_METHOD("get_tailpipe_lp"), &MoVeExhaust::get_tailpipe_lp);
    ClassDB::bind_method(D_METHOD("set_exhaust_echo_strength", "value"), &MoVeExhaust::set_exhaust_echo_strength);
    ClassDB::bind_method(D_METHOD("get_exhaust_echo_strength"), &MoVeExhaust::get_exhaust_echo_strength);
    ClassDB::bind_method(D_METHOD("set_exhaust_echo_delay", "value"), &MoVeExhaust::set_exhaust_echo_delay);
    ClassDB::bind_method(D_METHOD("get_exhaust_echo_delay"), &MoVeExhaust::get_exhaust_echo_delay);
    // Burble
    ClassDB::bind_method(D_METHOD("set_enable_burble", "value"), &MoVeExhaust::set_enable_burble);
    ClassDB::bind_method(D_METHOD("get_enable_burble"), &MoVeExhaust::get_enable_burble);
    ClassDB::bind_method(D_METHOD("set_burble_intensity", "value"), &MoVeExhaust::set_burble_intensity);
    ClassDB::bind_method(D_METHOD("get_burble_intensity"), &MoVeExhaust::get_burble_intensity);

    ADD_GROUP("Engine", "");
    ADD_PROPERTY(PropertyInfo(Variant::INT, "cylinders"), "set_cylinders", "get_cylinders");
    ADD_PROPERTY(PropertyInfo(Variant::INT, "strokes"), "set_strokes", "get_strokes");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "max_rpm"), "set_max_rpm", "get_max_rpm");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "idle_rpm"), "set_idle_rpm", "get_idle_rpm");

    // Sound Shape
    ADD_GROUP("Sound Shape", "");
    ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "firing_pattern"), "set_firing_pattern", "get_firing_pattern");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "duty_cycle"), "set_duty_cycle", "get_duty_cycle");
    ADD_PROPERTY(PropertyInfo(Variant::INT, "wave_quality"), "set_wave_quality", "get_wave_quality");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "starting_volume"), "set_starting_volume", "get_starting_volume");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "rumble_resonance"), "set_rumble_resonance", "get_rumble_resonance");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "pattern_strength"), "set_pattern_strength", "get_pattern_strength");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "lowpass_floor"), "set_lowpass_floor", "get_lowpass_floor");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "lowpass_ceiling"), "set_lowpass_ceiling", "get_lowpass_ceiling");

    // Throttle
    ADD_GROUP("Throttle", "");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "throttle_intake_gain"), "set_throttle_intake_gain", "get_throttle_intake_gain");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "throttle_attack_sharpness"), "set_throttle_attack_sharpness", "get_throttle_attack_sharpness");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "throttle_brightness_boost"), "set_throttle_brightness_boost", "get_throttle_brightness_boost");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "throttle_volume_gain"), "set_throttle_volume_gain", "get_throttle_volume_gain");

    // Muffler
    ADD_GROUP("Muffler", "");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "muff_resonance"), "set_muff_resonance", "get_muff_resonance");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "muff_damping"), "set_muff_damping", "get_muff_damping");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "tailpipe_lp"), "set_tailpipe_lp", "get_tailpipe_lp");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "exhaust_echo_strength"), "set_exhaust_echo_strength", "get_exhaust_echo_strength");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "exhaust_echo_delay"), "set_exhaust_echo_delay", "get_exhaust_echo_delay");

    // Burble
    ADD_GROUP("Burble", "");
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "enable_burble"), "set_enable_burble", "get_enable_burble");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "burble_intensity"), "set_burble_intensity", "get_burble_intensity");
}