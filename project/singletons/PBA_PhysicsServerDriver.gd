extends Node


func _physics_process(delta : float) -> void:
	PBAPhysicsServer.step(delta)
