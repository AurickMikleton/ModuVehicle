extends Node2D

@onready var line: Line2D = $Line

# graph settings
const SAMPLE_COUNT := 200
const GRAPH_WIDTH := 800.0
const GRAPH_HEIGHT := 400.0
const RPM_MIN := 800.0
const RPM_MAX := 7000.0

const NEW_MO_VE_ENGINE = preload("uid://valdgkwegmbq")

var torque_func: Callable = NEW_MO_VE_ENGINE.engine_torque

func _ready() -> void:
	draw_graph()

func draw_graph() -> void:
	var points: Array[Vector2] = []
	
	for i in range(SAMPLE_COUNT):
		var t := float(i) / (SAMPLE_COUNT - 1)
	
		# convert sample index → RPM
		var rpm : float = lerp(RPM_MIN, RPM_MAX, t)
	
		# torque value from the function
		var torque : float = torque_func.call(rpm)
		print(torque)
	
		# Normalize to graph coordinates
		var x := t * GRAPH_WIDTH
		var y := GRAPH_HEIGHT - (torque / get_max_torque()) * GRAPH_HEIGHT
	
		points.append(Vector2(x, y))
	
	line.points = points


func get_max_torque() -> float:
	var max_val := 0.0
	for i in range(SAMPLE_COUNT):
		var t := float(i) / (SAMPLE_COUNT - 1)
		var rpm : float = lerp(RPM_MIN, RPM_MAX, t)
		max_val = max(max_val, torque_func.call(rpm))
	return max_val
