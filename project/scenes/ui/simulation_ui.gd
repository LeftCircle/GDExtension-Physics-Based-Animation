extends Control

signal paused(status : bool)
signal step(amount : int)

func _on_pause_button_toggled(toggled_on: bool) -> void:   
	paused.emit(toggled_on)


func _on_step_forward_button_pressed() -> void:
	step.emit(1)
