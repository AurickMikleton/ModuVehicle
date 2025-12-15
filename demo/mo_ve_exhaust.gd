extends MoVeExhaust

# Called when the node enters the scene tree for the first time.
func _ready() -> void:
	init()

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _physics_process(_delta):
	set_rpm(engine.get_current_rpm())
	set_throttle(engine.get_throttle())
	fill_buffer()
