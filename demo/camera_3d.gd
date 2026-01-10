# ChaseCamera3D.gd (Godot 4.x)
extends Camera3D

@export var target_path: NodePath
@export var distance: float = 6.0
@export var height: float = 2.0
@export var follow_smooth: float = 10.0
@export var rotate_smooth: float = 12.0
@export var pitch_degrees: float = -12.0
@export var collision_margin: float = 0.25

@export var yaw_degrees: float = 0.0

var _target: Node3D

@export var mouse_sens: float = 0.12

func _unhandled_input(event: InputEvent) -> void:
	if event is InputEventMouseMotion and Input.is_mouse_button_pressed(MOUSE_BUTTON_RIGHT):
		yaw_degrees -= event.relative.x * mouse_sens

func _ready() -> void:
	_target = get_node_or_null(target_path) as Node3D
	if _target == null:
		push_error("ChaseCamera3D: target_path is not set or not a Node3D.")
		set_physics_process(false)

func _physics_process(delta: float) -> void:
	var desired_yaw := deg_to_rad(yaw_degrees)
	var new_yaw := lerp_angle(rotation.y, desired_yaw, 1.0 - exp(-rotate_smooth * delta))

	var anchor := _target.global_position + Vector3.UP * height

	var back := -Basis(Vector3.UP, new_yaw).z.normalized()
	var desired_pos := anchor + back * distance

	var space := get_world_3d().direct_space_state
	var query := PhysicsRayQueryParameters3D.create(anchor, desired_pos)
	query.exclude = [_target]
	query.collide_with_areas = false
	query.collide_with_bodies = true

	var hit := space.intersect_ray(query)

	var final_pos := desired_pos
	if hit.size() > 0:
		var hit_pos: Vector3 = hit["position"]
		final_pos = hit_pos + (anchor - hit_pos).normalized() * collision_margin

	global_position = global_position.lerp(final_pos, 1.0 - exp(-follow_smooth * delta))

	rotation = Vector3(deg_to_rad(pitch_degrees), new_yaw, 0.0)
