#include "gearbox_spec.hpp"

namespace godot {

GearboxSpec::GearboxSpec() {
    forward_ratios.push_back(3.66f);
    forward_ratios.push_back(2.43f);
    forward_ratios.push_back(1.69f);
    forward_ratios.push_back(1.31f);
    forward_ratios.push_back(1.00f);
    forward_ratios.push_back(0.74f);
}

void GearboxSpec::_bind_methods() {
    // godot-cpp requires a getter even for non-value category entries.
    ClassDB::bind_method(D_METHOD("_get_inspector_category"), &GearboxSpec::_get_inspector_category);
    ClassDB::bind_method(D_METHOD("set_display_name", "value"), &GearboxSpec::set_display_name);
    ClassDB::bind_method(D_METHOD("get_display_name"), &GearboxSpec::get_display_name);
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "display_name"),
        "set_display_name", "get_display_name");

    ClassDB::bind_method(D_METHOD("set_forward_ratios", "value"), &GearboxSpec::set_forward_ratios);
    ClassDB::bind_method(D_METHOD("get_forward_ratios"), &GearboxSpec::get_forward_ratios);
    ADD_PROPERTY(PropertyInfo(Variant::PACKED_FLOAT32_ARRAY, "forward_ratios"),
        "set_forward_ratios", "get_forward_ratios");

    ClassDB::bind_method(D_METHOD("set_reverse_ratio", "value"), &GearboxSpec::set_reverse_ratio);
    ClassDB::bind_method(D_METHOD("get_reverse_ratio"), &GearboxSpec::get_reverse_ratio);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "reverse_ratio", PROPERTY_HINT_RANGE, "0.1,5.0,0.01"),
        "set_reverse_ratio", "get_reverse_ratio");

    ClassDB::bind_method(D_METHOD("set_efficiency", "value"), &GearboxSpec::set_efficiency);
    ClassDB::bind_method(D_METHOD("get_efficiency"), &GearboxSpec::get_efficiency);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "efficiency", PROPERTY_HINT_RANGE, "0.0,1.0,0.01"),
        "set_efficiency", "get_efficiency");

    ClassDB::bind_method(D_METHOD("set_automatic", "value"), &GearboxSpec::set_automatic);
    ClassDB::bind_method(D_METHOD("get_automatic"), &GearboxSpec::get_automatic);
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "automatic"),
        "set_automatic", "get_automatic");

    ClassDB::bind_method(D_METHOD("set_shift_duration", "value"), &GearboxSpec::set_shift_duration);
    ClassDB::bind_method(D_METHOD("get_shift_duration"), &GearboxSpec::get_shift_duration);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "shift_duration", PROPERTY_HINT_RANGE, "0.0,1.0,0.01"),
        "set_shift_duration", "get_shift_duration");

    ClassDB::bind_method(D_METHOD("set_post_shift_hold", "value"), &GearboxSpec::set_post_shift_hold);
    ClassDB::bind_method(D_METHOD("get_post_shift_hold"), &GearboxSpec::get_post_shift_hold);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "post_shift_hold", PROPERTY_HINT_RANGE, "0.0,2.0,0.01"),
        "set_post_shift_hold", "get_post_shift_hold");

    ClassDB::bind_method(D_METHOD("set_upshift_fraction", "value"), &GearboxSpec::set_upshift_fraction);
    ClassDB::bind_method(D_METHOD("get_upshift_fraction"), &GearboxSpec::get_upshift_fraction);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "upshift_fraction", PROPERTY_HINT_RANGE, "0.1,1.0,0.01"),
        "set_upshift_fraction", "get_upshift_fraction");

    ClassDB::bind_method(D_METHOD("set_downshift_fraction", "value"), &GearboxSpec::set_downshift_fraction);
    ClassDB::bind_method(D_METHOD("get_downshift_fraction"), &GearboxSpec::get_downshift_fraction);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "downshift_fraction", PROPERTY_HINT_RANGE, "0.1,1.0,0.01"),
        "set_downshift_fraction", "get_downshift_fraction");

    ADD_PROPERTY(PropertyInfo(Variant::NIL, "Clutch / converter", PROPERTY_HINT_NONE,
        "", PROPERTY_USAGE_CATEGORY), "", "_get_inspector_category");

    ClassDB::bind_method(D_METHOD("set_engage_rpm", "value"), &GearboxSpec::set_engage_rpm);
    ClassDB::bind_method(D_METHOD("get_engage_rpm"), &GearboxSpec::get_engage_rpm);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "engage_rpm", PROPERTY_HINT_RANGE, "0.0,5000.0,10.0"),
        "set_engage_rpm", "get_engage_rpm");

    ClassDB::bind_method(D_METHOD("set_full_engagement_rpm", "value"), &GearboxSpec::set_full_engagement_rpm);
    ClassDB::bind_method(D_METHOD("get_full_engagement_rpm"), &GearboxSpec::get_full_engagement_rpm);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "full_engagement_rpm", PROPERTY_HINT_RANGE, "0.0,5000.0,10.0"),
        "set_full_engagement_rpm", "get_full_engagement_rpm");

    ClassDB::bind_method(D_METHOD("set_clutch_capacity_nm", "value"), &GearboxSpec::set_clutch_capacity_nm);
    ClassDB::bind_method(D_METHOD("get_clutch_capacity_nm"), &GearboxSpec::get_clutch_capacity_nm);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "clutch_capacity_nm", PROPERTY_HINT_RANGE, "10.0,2000.0,10.0"),
        "set_clutch_capacity_nm", "get_clutch_capacity_nm");

    ClassDB::bind_method(D_METHOD("set_slip_gain", "value"), &GearboxSpec::set_slip_gain);
    ClassDB::bind_method(D_METHOD("get_slip_gain"), &GearboxSpec::get_slip_gain);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "slip_gain", PROPERTY_HINT_RANGE, "0.1,30.0,0.1"),
        "set_slip_gain", "get_slip_gain");

}

void GearboxSpec::set_display_name(const String &value) {
    if (display_name == value) {
        return;
    }
    display_name = value;
    emit_changed();
}

String GearboxSpec::get_display_name() const {
    return display_name;
}

void GearboxSpec::set_forward_ratios(const PackedFloat32Array &value) {
    forward_ratios = value;
    emit_changed();
}

PackedFloat32Array GearboxSpec::get_forward_ratios() const {
    return forward_ratios;
}

void GearboxSpec::set_reverse_ratio(double value) {
    if (reverse_ratio == value) {
        return;
    }
    reverse_ratio = value;
    emit_changed();
}

double GearboxSpec::get_reverse_ratio() const {
    return reverse_ratio;
}

void GearboxSpec::set_efficiency(double value) {
    if (efficiency == value) {
        return;
    }
    efficiency = value;
    emit_changed();
}

double GearboxSpec::get_efficiency() const {
    return efficiency;
}

void GearboxSpec::set_automatic(bool value) {
    if (automatic == value) {
        return;
    }
    automatic = value;
    emit_changed();
}

bool GearboxSpec::get_automatic() const {
    return automatic;
}

void GearboxSpec::set_shift_duration(double value) {
    if (shift_duration == value) {
        return;
    }
    shift_duration = value;
    emit_changed();
}

double GearboxSpec::get_shift_duration() const {
    return shift_duration;
}

void GearboxSpec::set_post_shift_hold(double value) {
    if (post_shift_hold == value) {
        return;
    }
    post_shift_hold = value;
    emit_changed();
}

double GearboxSpec::get_post_shift_hold() const {
    return post_shift_hold;
}

void GearboxSpec::set_upshift_fraction(double value) {
    if (upshift_fraction == value) {
        return;
    }
    upshift_fraction = value;
    emit_changed();
}

double GearboxSpec::get_upshift_fraction() const {
    return upshift_fraction;
}

void GearboxSpec::set_downshift_fraction(double value) {
    if (downshift_fraction == value) {
        return;
    }
    downshift_fraction = value;
    emit_changed();
}

double GearboxSpec::get_downshift_fraction() const {
    return downshift_fraction;
}

void GearboxSpec::set_engage_rpm(double value) {
    if (engage_rpm == value) {
        return;
    }
    engage_rpm = value;
    emit_changed();
}

double GearboxSpec::get_engage_rpm() const {
    return engage_rpm;
}

void GearboxSpec::set_full_engagement_rpm(double value) {
    if (full_engagement_rpm == value) {
        return;
    }
    full_engagement_rpm = value;
    emit_changed();
}

double GearboxSpec::get_full_engagement_rpm() const {
    return full_engagement_rpm;
}

void GearboxSpec::set_clutch_capacity_nm(double value) {
    if (clutch_capacity_nm == value) {
        return;
    }
    clutch_capacity_nm = value;
    emit_changed();
}

double GearboxSpec::get_clutch_capacity_nm() const {
    return clutch_capacity_nm;
}

void GearboxSpec::set_slip_gain(double value) {
    if (slip_gain == value) {
        return;
    }
    slip_gain = value;
    emit_changed();
}

double GearboxSpec::get_slip_gain() const {
    return slip_gain;
}

} // namespace godot

godot::Variant godot::GearboxSpec::_get_inspector_category() const {
    return Variant();
}
