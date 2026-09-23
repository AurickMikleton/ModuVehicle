#include "engine_sound_layout.hpp"

namespace godot {

EngineSoundLayout::EngineSoundLayout() {
    firing_pattern.push_back(1.0f);
}

void EngineSoundLayout::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_display_name", "value"), &EngineSoundLayout::set_display_name);
    ClassDB::bind_method(D_METHOD("get_display_name"), &EngineSoundLayout::get_display_name);
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "display_name"),
        "set_display_name", "get_display_name");

    ClassDB::bind_method(D_METHOD("set_cylinders", "value"), &EngineSoundLayout::set_cylinders);
    ClassDB::bind_method(D_METHOD("get_cylinders"), &EngineSoundLayout::get_cylinders);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "cylinders", PROPERTY_HINT_RANGE, "1,16,1"),
        "set_cylinders", "get_cylinders");

    ClassDB::bind_method(D_METHOD("set_strokes", "value"), &EngineSoundLayout::set_strokes);
    ClassDB::bind_method(D_METHOD("get_strokes"), &EngineSoundLayout::get_strokes);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "strokes", PROPERTY_HINT_ENUM, "Two-stroke:2,Four-stroke:4"),
        "set_strokes", "get_strokes");

    ClassDB::bind_method(D_METHOD("set_firing_pattern", "value"), &EngineSoundLayout::set_firing_pattern);
    ClassDB::bind_method(D_METHOD("get_firing_pattern"), &EngineSoundLayout::get_firing_pattern);
    ADD_PROPERTY(PropertyInfo(Variant::PACKED_FLOAT32_ARRAY, "firing_pattern"),
        "set_firing_pattern", "get_firing_pattern");

}

void EngineSoundLayout::set_display_name(const String &value) {
    if (display_name == value) {
        return;
    }
    display_name = value;
    emit_changed();
}

String EngineSoundLayout::get_display_name() const {
    return display_name;
}

void EngineSoundLayout::set_cylinders(int64_t value) {
    if (cylinders == value) {
        return;
    }
    cylinders = value;
    emit_changed();
}

int64_t EngineSoundLayout::get_cylinders() const {
    return cylinders;
}

void EngineSoundLayout::set_strokes(int64_t value) {
    if (strokes == value) {
        return;
    }
    strokes = value;
    emit_changed();
}

int64_t EngineSoundLayout::get_strokes() const {
    return strokes;
}

void EngineSoundLayout::set_firing_pattern(const PackedFloat32Array &value) {
    firing_pattern = value;
    emit_changed();
}

PackedFloat32Array EngineSoundLayout::get_firing_pattern() const {
    return firing_pattern;
}

} // namespace godot
