#include "wheel.hpp"

void ModuWheel::_bind_methods() {
    godot::ClassDB::bind_method(D_METHOD("add", "value"), &ModuWheel::add);
    godot::ClassDB::bind_method(D_METHOD("get_total"), &ModuWheel::get_total);
}

ModuWheel::ModuWheel() {
    m_sum = 0;
}

void ModuWheel::add(int value) {
    m_sum += value;
}

int ModuWheel::get_total() const {
    return m_sum;
}