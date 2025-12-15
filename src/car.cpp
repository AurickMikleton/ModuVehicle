#include "car.hpp"

using namespace godot;

void MoVeCar::set_engine(Ref<MoVeEngine> value) {m_engine = value;}
Ref<MoVeEngine> MoVeCar::get_engine() const {return m_engine;}

void MoVeCar::set_transmission(Ref<MoVeTransmission> value) {m_transmission = value;}
Ref<MoVeTransmission> MoVeCar::get_transmission() const {return m_transmission;}

void MoVeCar::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_engine", "value"), &MoVeCar::set_engine);
    ClassDB::bind_method(D_METHOD("get_engine"), &MoVeCar::get_engine);
    ClassDB::bind_method(D_METHOD("set_transmission", "value"), &MoVeCar::set_transmission);
    ClassDB::bind_method(D_METHOD("get_transmission"), &MoVeCar::get_transmission);

    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "engine", PROPERTY_HINT_RESOURCE_TYPE, "MoVeEngine"), "set_engine", "get_engine");
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "transmission", PROPERTY_HINT_RESOURCE_TYPE, "MoVeTransmission"), "set_transmission", "get_transmission");
}