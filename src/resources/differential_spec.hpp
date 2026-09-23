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

class DifferentialSpec : public Resource {
    GDCLASS(DifferentialSpec, Resource)

private:
    String display_name = "Limited-slip differential";
    double final_drive = 3.90;
    double efficiency = 0.96;
    double locking_strength = 0.22;

protected:
    static void _bind_methods();

public:
    DifferentialSpec();

    void set_display_name(const String &value);
    String get_display_name() const;

    void set_final_drive(double value);
    double get_final_drive() const;

    void set_efficiency(double value);
    double get_efficiency() const;

    void set_locking_strength(double value);
    double get_locking_strength() const;

};

} // namespace godot
