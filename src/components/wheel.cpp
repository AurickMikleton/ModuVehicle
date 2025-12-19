#include "wheel.hpp"

void MoVeWheel::update_suspension() {
    if (!is_colliding()) return;

    Vector3 contact = get_collision_point();
    Vector3 up_direction = get_global_transform().get_basis().get_column(1);
    float spring_length = get_global_position().distance_to(contact);
    float offset = m_resting_distnace - spring_length;

    float spring_force = m_spring_strength * offset;
    Vector3 force_vector = up_direction * spring_force;
    Vector3 force_position_offset = contact - get_global_position();
    // apply_force(force_vector, force_position_offset);
}

void MoVeWheel::_bind_methods() {
    godot::ClassDB::bind_method(D_METHOD("update_suspension"), &MoVeWheel::update_suspension);
}