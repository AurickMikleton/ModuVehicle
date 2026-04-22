#include "car.hpp"

#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

void MoVeCar::_ready() {
	//pass
}

void MoVeCar::update() {
	//TODO orchestrate other update functions; less requisite boilerplate
}

void MoVeCar::update_wheels() {
	wheels.clear();
	wheels.reserve(m_wheel_paths.size());

	for (int i = 0; i < m_wheel_paths.size(); i++) {
		NodePath path = m_wheel_paths[i];
		if (!has_node(path)) {
			WARN_PRINT(vformat("Wheel path not found: %s", path));
			continue;
		}
		MoVeWheel *wheel = get_node<MoVeWheel>(path);
		if (wheel)
			wheels.push_back(wheel);
	}
}

void MoVeCar::update_suspension(float delta) {
	for (auto &wheel : wheels) {
		if (!wheel->is_colliding()) {
			wheel->set_normal_force(0.0f);
			continue;
		}

		Vector3 target = wheel->get_target_position();
		target.y = (-(wheel->m_resting_distnace + wheel->m_wheel_radius + 0.2));
		wheel->set_target_position(target);

		Vector3 contact = wheel->get_collision_point();
		Vector3 up_direction = wheel->get_global_transform().get_basis().get_column(1);
		float spring_length = wheel->get_global_position().distance_to(contact) - wheel->m_wheel_radius;

		// clamp physically valid spring length
		spring_length = Math::clamp(spring_length, 0.0f, wheel->m_resting_distnace);

		// compression only
		float compression = wheel->m_resting_distnace - spring_length;
		if (compression <= 0.0f) {
			wheel->set_normal_force(0.0f);
			continue;
		}

		Node3D *wheel_mesh = wheel->get_node<Node3D>("wheel");
		Vector3 mesh_target = wheel_mesh->get_position();
		mesh_target.y = -spring_length;
		wheel_mesh->set_position(mesh_target);

		float spring_force = wheel->m_spring_strength * compression;

		Vector3 world_velocity = get_linear_velocity() + get_angular_velocity().cross(contact - get_global_position());
		float relative_velocity = up_direction.dot(world_velocity);
		float spring_damp_force = relative_velocity * wheel->m_spring_damping;
		float normal_force = Math::max(0.0f, spring_force - spring_damp_force);

		wheel->set_normal_force(normal_force);

		Vector3 force_vector = up_direction * (spring_force - spring_damp_force);
		Vector3 force_position_offset = contact - get_global_position();
		apply_force(force_vector, force_position_offset);
	}
}

// Goal layout for update_acceleration
//engine_torque = m_engine->engine_torque(engine_rpm);
//clutch_torque = m_transmission->clutch_torque(engine_rpm, slip);
//m_engine->apply_load(clutch_torque, delta);
//m_transmission->apply_input_torque(clutch_torque);
//wheel_torque = m_transmission->output_torque(clutch_torque);

void MoVeCar::update_acceleration(float delta) {
	int powered = 0;
	float sum_wheel_omega = 0.0f;
	float sum_ground_speed = 0.0f;

	float gear = m_transmission->get_gear_ratio();

	int i = 0;
	for (auto &wheel : wheels) {
		i++;
		wheel->cache_contact_kinematics(
			get_linear_velocity(),
			get_angular_velocity(),
			get_global_position()
		);

		wheel->update_visual_rotation(delta);

		UtilityFunctions::print(vformat(
			"wheel %d: colliding=%s powered=%s ang_vel=%.3f ground_speed=%.3f",
			i,
			wheel->is_colliding() ? "true" : "false",
			wheel->get_is_powered() ? "true" : "false",
			wheel->get_angular_velocity(),
			wheel->get_ground_speed()
		));

		if (!wheel->is_driveline_active())
			continue;

		powered++;
		sum_wheel_omega += wheel->get_angular_velocity();
		sum_ground_speed += wheel->get_cached_ground_speed();
	}

	if (Math::is_zero_approx(gear) || powered == 0) {
		m_engine->set_reflected_load(0.0f);
		m_engine->update_rpm(delta);
		return;
	}

	float avg_wheel_omega = sum_wheel_omega / (float)powered;
	float avg_speed = sum_ground_speed / (float)powered;

	float engine_rpm = (float)m_engine->get_current_rpm();
	float engine_omega = engine_rpm * (Math_TAU / 60.0f);
	float target_wheel_omega = engine_omega / gear;
	float trans_input_omega = avg_wheel_omega * gear;

	float slip_omega = engine_omega - trans_input_omega;


	UtilityFunctions::print(vformat(
		"powered_count=%d sum_wheel_omega=%.3f avg_wheel_omega=%.3f gear=%.3f trans_input_omega=%.3f",
		powered,
		sum_wheel_omega,
		avg_wheel_omega,
		gear,
		trans_input_omega
	));

	UtilityFunctions::print(vformat(
		"rpm_before=%.2f trans_in=%.2f slip=%.2f",
		engine_rpm,
		trans_input_omega * (60.0f / Math_TAU),
		slip_omega
	));


	float clutch_torque = m_transmission->clutch_torque(engine_rpm, slip_omega);

	m_engine->set_reflected_load(Math::abs(clutch_torque));
	m_engine->update_rpm(delta);

	float driveshaft_torque = clutch_torque * gear;
	float torque_per_wheel = driveshaft_torque / (float)powered;

	for (auto &wheel : wheels) {
		if (!wheel->is_driveline_active())
			continue;

		wheel->apply_drive_torque_and_integrate(torque_per_wheel, delta);
		apply_force(
			wheel->get_cached_longitudinal_force_vector(),
			wheel->get_cached_force_offset()
		);
	}
}

void MoVeCar::update_traction(float delta) {
	for (auto &wheel : wheels) {
		if (!wheel->is_colliding()) {
			continue;
		}
		Vector3 side_direction = wheel->get_global_transform().get_basis().get_column(0).normalized();

		Node3D *wheel_mesh = wheel->get_node<Node3D>("wheel");

		Vector3 position = wheel_mesh->get_global_position(); // World-space position of the wheel mesh
		Vector3 offset = position - get_global_position(); // Vector from COM → wheel point

		// Point velocity at wheel mesh
		Vector3 tire_velocity =
				get_linear_velocity() +
				get_angular_velocity().cross(offset);

		float steering_x_velocity = side_direction.dot(tire_velocity);

		float x_traction = 1.0f;
		float gravity = (float)ProjectSettings::get_singleton()
								->get_setting("physics/3d/default_gravity");
		Vector3 x_force =
				-side_direction *
				steering_x_velocity *
				x_traction *
				((get_mass() * gravity) / (float)wheels.size());

		Vector3 force_position = wheel_mesh->get_global_position() - get_global_position();
		apply_force(x_force, force_position);
	}
}

void MoVeCar::set_engine(Ref<MoVeEngine> value) { m_engine = value; }
Ref<MoVeEngine> MoVeCar::get_engine() const { return m_engine; }

void MoVeCar::set_transmission(Ref<MoVeTransmission> value) { m_transmission = value; }
Ref<MoVeTransmission> MoVeCar::get_transmission() const { return m_transmission; }

void MoVeCar::set_wheel_paths(const TypedArray<NodePath> &p_paths) {
	m_wheel_paths = p_paths;
	call_deferred("update_wheels");
}
TypedArray<NodePath> MoVeCar::get_wheel_paths() const { return m_wheel_paths; }

void MoVeCar::_bind_methods() {
	ClassDB::bind_method(D_METHOD("update"), &MoVeCar::update);
	ClassDB::bind_method(D_METHOD("update_wheels"), &MoVeCar::update_wheels);
	ClassDB::bind_method(D_METHOD("update_suspension"), &MoVeCar::update_suspension);
	ClassDB::bind_method(D_METHOD("update_acceleration"), &MoVeCar::update_acceleration);
	ClassDB::bind_method(D_METHOD("update_traction"), &MoVeCar::update_traction);

	ClassDB::bind_method(D_METHOD("set_engine", "value"), &MoVeCar::set_engine);
	ClassDB::bind_method(D_METHOD("get_engine"), &MoVeCar::get_engine);
	ClassDB::bind_method(D_METHOD("set_transmission", "value"), &MoVeCar::set_transmission);
	ClassDB::bind_method(D_METHOD("get_transmission"), &MoVeCar::get_transmission);
	ClassDB::bind_method(D_METHOD("set_wheel_paths", "value"), &MoVeCar::set_wheel_paths);
	ClassDB::bind_method(D_METHOD("get_wheel_paths"), &MoVeCar::get_wheel_paths);

	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "engine", PROPERTY_HINT_RESOURCE_TYPE, "MoVeEngine"), "set_engine", "get_engine");
	ADD_PROPERTY(
			PropertyInfo(Variant::OBJECT, "transmission", PROPERTY_HINT_RESOURCE_TYPE, "MoVeTransmission"),
			"set_transmission",
			"get_transmission");
	ADD_PROPERTY(
			PropertyInfo(Variant::ARRAY, "wheels", PROPERTY_HINT_ARRAY_TYPE, "NodePath"),
			"set_wheel_paths",
			"get_wheel_paths");
}
