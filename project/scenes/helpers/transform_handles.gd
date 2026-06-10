extends Node3D

var transform_direction : Vector3 = Vector3.RIGHT
var follow_mouse = false
var last_mouse_position : Vector2
var current_mouse_position : Vector2

@onready var n2d = $Node2D

func _process(delta: float) -> void:
	if follow_mouse:
		if !Input.is_action_pressed("m1"):
			follow_mouse = false
			return
		current_mouse_position = n2d.get_global_mouse_position()
		var dist = (current_mouse_position - last_mouse_position).length() * 0.001
		print(dist)
		global_position += transform_direction * dist
		last_mouse_position = current_mouse_position

func _on_area_3d_selected(dir: Vector3) -> void:
	transform_direction = dir
	follow_mouse = true
	print("Selected")
	last_mouse_position = n2d.get_global_mouse_position()
