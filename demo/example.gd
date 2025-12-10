extends Node


func _ready() -> void:
	var example := ExampleClass.new()
	example.print_type(example)
	
	var wheel := ModuWheel.new()
	wheel.add(2)
	wheel.add(3)
	wheel.add(4)
	print(wheel.get_total())
