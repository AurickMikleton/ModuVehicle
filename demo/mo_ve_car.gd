extends MoVeCar


# Called when the node enters the scene tree for the first time.
func _ready() -> void:
	pass # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _physics_process(delta: float) -> void:
	update()
	update_suspension(delta)
	update_acceleration(delta)
	update_traction(delta)
	engine.update_rpm(delta)
	
	if Input.is_action_just_pressed("shift_up"): transmission.shift_up()
	if Input.is_action_just_pressed("shift_down"): transmission.shift_down()
	print(engine.get_current_rpm())
	#print(transmission.get_current_gear())
	
	if Input.is_action_pressed("throttle"):
		engine.set_throttle(1.0)
	else:
		engine.set_throttle(0.0)
	
	var turn_input = Input.get_axis("right", "left")
	if turn_input:
		$FrontLeft.rotation.y = clampf($FrontLeft.rotation.y + turn_input * delta,
			deg_to_rad(-29), deg_to_rad(29))
		$FrontRight.rotation.y = clampf($FrontRight.rotation.y + turn_input * delta,
			deg_to_rad(-29), deg_to_rad(29))
	else:
		$FrontLeft.rotation.y = move_toward($FrontLeft.rotation.y, 0, 7.0 * delta)
		$FrontRight.rotation.y = move_toward($FrontRight.rotation.y, 0, 7.0 * delta)
