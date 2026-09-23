#include "suspension_spec.hpp"

namespace godot {

SuspensionSpec::SuspensionSpec() {
}

void SuspensionSpec::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_display_name", "value"), &SuspensionSpec::set_display_name);
    ClassDB::bind_method(D_METHOD("get_display_name"), &SuspensionSpec::get_display_name);
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "display_name"),
        "set_display_name", "get_display_name");

    ClassDB::bind_method(D_METHOD("set_rest_length", "value"), &SuspensionSpec::set_rest_length);
    ClassDB::bind_method(D_METHOD("get_rest_length"), &SuspensionSpec::get_rest_length);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "rest_length", PROPERTY_HINT_RANGE, "0.05,1.0,0.01"),
        "set_rest_length", "get_rest_length");

    ClassDB::bind_method(D_METHOD("set_travel", "value"), &SuspensionSpec::set_travel);
    ClassDB::bind_method(D_METHOD("get_travel"), &SuspensionSpec::get_travel);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "travel", PROPERTY_HINT_RANGE, "0.01,0.8,0.01"),
        "set_travel", "get_travel");

    ClassDB::bind_method(D_METHOD("set_spring_rate", "value"), &SuspensionSpec::set_spring_rate);
    ClassDB::bind_method(D_METHOD("get_spring_rate"), &SuspensionSpec::get_spring_rate);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "spring_rate", PROPERTY_HINT_RANGE, "1000.0,150000.0,500.0"),
        "set_spring_rate", "get_spring_rate");

    ClassDB::bind_method(D_METHOD("set_compression_damping", "value"), &SuspensionSpec::set_compression_damping);
    ClassDB::bind_method(D_METHOD("get_compression_damping"), &SuspensionSpec::get_compression_damping);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "compression_damping", PROPERTY_HINT_RANGE, "100.0,20000.0,100.0"),
        "set_compression_damping", "get_compression_damping");

    ClassDB::bind_method(D_METHOD("set_rebound_damping", "value"), &SuspensionSpec::set_rebound_damping);
    ClassDB::bind_method(D_METHOD("get_rebound_damping"), &SuspensionSpec::get_rebound_damping);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "rebound_damping", PROPERTY_HINT_RANGE, "100.0,20000.0,100.0"),
        "set_rebound_damping", "get_rebound_damping");

    ClassDB::bind_method(D_METHOD("set_anti_roll_share", "value"), &SuspensionSpec::set_anti_roll_share);
    ClassDB::bind_method(D_METHOD("get_anti_roll_share"), &SuspensionSpec::get_anti_roll_share);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "anti_roll_share", PROPERTY_HINT_RANGE, "0.0,1.0,0.01"),
        "set_anti_roll_share", "get_anti_roll_share");

}

void SuspensionSpec::set_display_name(const String &value) {
    if (display_name == value) {
        return;
    }
    display_name = value;
    emit_changed();
}

String SuspensionSpec::get_display_name() const {
    return display_name;
}

void SuspensionSpec::set_rest_length(double value) {
    if (rest_length == value) {
        return;
    }
    rest_length = value;
    emit_changed();
}

double SuspensionSpec::get_rest_length() const {
    return rest_length;
}

void SuspensionSpec::set_travel(double value) {
    if (travel == value) {
        return;
    }
    travel = value;
    emit_changed();
}

double SuspensionSpec::get_travel() const {
    return travel;
}

void SuspensionSpec::set_spring_rate(double value) {
    if (spring_rate == value) {
        return;
    }
    spring_rate = value;
    emit_changed();
}

double SuspensionSpec::get_spring_rate() const {
    return spring_rate;
}

void SuspensionSpec::set_compression_damping(double value) {
    if (compression_damping == value) {
        return;
    }
    compression_damping = value;
    emit_changed();
}

double SuspensionSpec::get_compression_damping() const {
    return compression_damping;
}

void SuspensionSpec::set_rebound_damping(double value) {
    if (rebound_damping == value) {
        return;
    }
    rebound_damping = value;
    emit_changed();
}

double SuspensionSpec::get_rebound_damping() const {
    return rebound_damping;
}

void SuspensionSpec::set_anti_roll_share(double value) {
    if (anti_roll_share == value) {
        return;
    }
    anti_roll_share = value;
    emit_changed();
}

double SuspensionSpec::get_anti_roll_share() const {
    return anti_roll_share;
}

} // namespace godot
