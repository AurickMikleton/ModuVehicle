#include "car.hpp"

using namespace godot;

void MoVeCar::aerodynamics() const {
    return;
}

void MoVeCar::_physics_process(double delta) {
	return;
}

void MoVeCar::set_aero_enabled(bool value) {m_aero_enabled = value;}
bool MoVeCar::get_aero_enabled() const {return m_aero_enabled;}

void MoVeCar::set_aero_up_force(double value) {m_aero_up_force = value;}
double MoVeCar::get_aero_up_force() const {return m_aero_up_force;}

void MoVeCar::set_aero_down_force(double value) {m_aero_down_force = value;}
double MoVeCar::get_aero_down_force() const {return m_aero_down_force;}

void MoVeCar::set_engine(Ref<MoVeEngine> value) {m_engine = value;}
Ref<MoVeEngine> MoVeCar::get_engine() const {return m_engine;}

MoVeCar::MoVeCar() {
    m_aero_enabled = true;
    m_aero_up_force = 0.0;
    m_aero_down_force = 0.0;
}

void MoVeCar::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_aero_enabled"), &MoVeCar::get_aero_enabled);
	ClassDB::bind_method(D_METHOD("set_aero_enabled", "value"), &MoVeCar::set_aero_enabled);
    ClassDB::bind_method(D_METHOD("get_aero_down_force"), &MoVeCar::get_aero_down_force);
	ClassDB::bind_method(D_METHOD("set_aero_down_force", "value"), &MoVeCar::set_aero_down_force);
    ClassDB::bind_method(D_METHOD("get_aero_up_force"), &MoVeCar::get_aero_up_force);
	ClassDB::bind_method(D_METHOD("set_aero_up_force", "value"), &MoVeCar::set_aero_up_force);

    ADD_GROUP("Aerodynamics", "aero_");
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "aero_enabled"), "set_aero_enabled", "get_aero_enabled");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "aero_down_force", PROPERTY_HINT_RANGE, "0,1,0.01"), "set_aero_down_force", "get_aero_down_force");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "aero_up_force", PROPERTY_HINT_RANGE, "0,1,0.01"), "set_aero_up_force", "get_aero_up_force");

	ClassDB::bind_method(D_METHOD("set_engine", "value"), &MoVeCar::set_engine);
    ClassDB::bind_method(D_METHOD("get_engine"), &MoVeCar::get_engine);

    ADD_GROUP("Components", "");
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "engine", PROPERTY_HINT_RESOURCE_TYPE, "MoVeEngine"), "set_engine", "get_engine");
}