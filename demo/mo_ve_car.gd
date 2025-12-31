extends MoVeCar


# Called when the node enters the scene tree for the first time.
func _ready() -> void:
	pass # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _physics_process(delta: float) -> void:
	update()
	update_suspension()
	update_acceleration(delta)
	if Input.is_action_just_pressed("shift_up"): transmission.shift_up()
	if Input.is_action_just_pressed("shift_down"): transmission.shift_down()
	print(transmission.get_current_gear())
	
	engine.update_rpm(delta)
	
	if Input.is_action_pressed("throttle"):
		engine.set_throttle(1.0)
	else:
		engine.set_throttle(0.0)
