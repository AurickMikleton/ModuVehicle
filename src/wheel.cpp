#include "wheel.hpp"

void MoVeWheel::_bind_methods() {
    godot::ClassDB::bind_method(D_METHOD("get_steering"), &MoVeWheel::get_steering);
}

bool MoVeWheel::get_steering() const {
    return m_steering;
}