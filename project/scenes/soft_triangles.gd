extends Node3D

@onready var physics_dt = ProjectSettings.get_setting("physics/common/physics_ticks_per_second") / 60.0

func _on_simulation_ui_paused(status: bool) -> void:
	print("Paused = ", status)
	PbaPhysicsServerDriver.set_physics_process(!status)


func _on_simulation_ui_step(amount: int) -> void:
	PBAPhysicsServer.step(amount * physics_dt)
