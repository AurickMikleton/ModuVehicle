#pragma once

#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/variant/string.hpp>
#include <godot_cpp/variant/vector3.hpp>
#include <godot_cpp/variant/packed_float32_array.hpp>
#include <godot_cpp/variant/typed_array.hpp>
#include <cstdint>

namespace godot {

class EngineSoundLayout : public Resource {
    GDCLASS(EngineSoundLayout, Resource)

private:
    // Acoustic configuration only; never read by vehicle physics.
    String display_name = "Inline-4";
    int64_t cylinders = 4;
    int64_t strokes = 4;
    // Relative firing intervals, copied into each synth instance.
    PackedFloat32Array firing_pattern;

protected:
    static void _bind_methods();

public:
    EngineSoundLayout();

    void set_display_name(const String &value);
    String get_display_name() const;

    void set_cylinders(int64_t value);
    int64_t get_cylinders() const;

    void set_strokes(int64_t value);
    int64_t get_strokes() const;

    void set_firing_pattern(const PackedFloat32Array &value);
    PackedFloat32Array get_firing_pattern() const;

};

} // namespace godot
