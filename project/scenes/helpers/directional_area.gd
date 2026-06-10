extends Area3D
class_name DirectionalCollision

signal selected(dir : Vector3)

@export var direction = Vector3.RIGHT


func _ready() -> void:
	input_event.connect(_on_selected)

func _on_selected(camera: Node, event: InputEvent, event_position: Vector3, normal : Vector3, shape_idx: int):
	if (event is InputEventMouseButton and event.pressed and event.button_index == MOUSE_BUTTON_LEFT):
		selected.emit(direction)
