#include "car.hpp"

void MoVeCar::_bind_methods() {
    godot::ClassDB::bind_method(D_METHOD("aerodynamics"), &MoVeCar::aerodynamics);
    godot::ClassDB::bind_method(D_METHOD("get_crank_rpm"), &MoVeCar::get_crank_rpm);
}

void MoVeCar::aerodynamics() const {
    return;
}

float MoVeCar::get_crank_rpm() const {
    return m_crank_shaft_rpm;
}