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

class SuspensionSpec : public Resource {
    GDCLASS(SuspensionSpec, Resource)

private:
    String display_name = "Sport suspension";
    double rest_length = 0.34;
    double travel = 0.20;
    double spring_rate = 35000.0;
    double compression_damping = 4200.0;
    double rebound_damping = 5200.0;
    double anti_roll_share = 0.35;

protected:
    static void _bind_methods();

public:
    SuspensionSpec();

    void set_display_name(const String &value);
    String get_display_name() const;

    void set_rest_length(double value);
    double get_rest_length() const;

    void set_travel(double value);
    double get_travel() const;

    void set_spring_rate(double value);
    double get_spring_rate() const;

    void set_compression_damping(double value);
    double get_compression_damping() const;

    void set_rebound_damping(double value);
    double get_rebound_damping() const;

    void set_anti_roll_share(double value);
    double get_anti_roll_share() const;

};

} // namespace godot
