extends Node2D

@onready var line: Line2D = $Line

const SAMPLE_COUNT := 200
const GRAPH_WIDTH := 800.0
const GRAPH_HEIGHT := 400.0
const RPM_MIN := 900.0
const RPM_MAX := 7000.0

const NEW_MO_VE_ENGINE = preload("uid://valdgkwegmbq")

var torque_func: Callable = NEW_MO_VE_ENGINE.engine_torque
var current_rpm: float = 900.0

func _ready() -> void:
	draw_graph()

func _process(delta):
	NEW_MO_VE_ENGINE.update_rpm(delta)
	current_rpm = NEW_MO_VE_ENGINE.get_current_rpm()
	
	queue_redraw()
	if Input.is_action_pressed("throttle"):
		NEW_MO_VE_ENGINE.set_throttle(1)
	else:
		NEW_MO_VE_ENGINE.set_throttle(0)

func draw_graph() -> void:
	var points: Array[Vector2] = []
	var max_torque := get_max_torque()
	
	for i in range(SAMPLE_COUNT):
		var t := float(i) / (SAMPLE_COUNT - 1)
		var rpm : float = lerp(RPM_MIN, RPM_MAX, t)
		var torque : float = torque_func.call(rpm)
	
		var x := t * GRAPH_WIDTH
		var y : float = GRAPH_HEIGHT - (torque / max_torque) * GRAPH_HEIGHT
	
		points.append(Vector2(x, y))
	
	line.points = PackedVector2Array(points)

func _draw() -> void:
	#if current_rpm >= RPM_MIN and current_rpm <= RPM_MAX:
	var t := (current_rpm - RPM_MIN) / (RPM_MAX - RPM_MIN)
	var x := t * GRAPH_WIDTH
	
	var pos_x := line.position.x
	var pos_y := line.position.y
	
	draw_line(
		Vector2(x + pos_x, 0 + pos_y),
		Vector2(x + pos_x, GRAPH_HEIGHT + pos_y),
		Color.WHITE,
		3.0
	)

func get_max_torque() -> float:
	var max_val := 0.0
	for i in range(SAMPLE_COUNT):
		var t := float(i) / (SAMPLE_COUNT - 1)
		var rpm : float = lerp(RPM_MIN, RPM_MAX, t)
		max_val = max(max_val, torque_func.call(rpm))
	return max_val
