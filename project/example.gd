extends Node


func _ready() -> void:
	var example := ExampleClass.new()
	example.print_type(example)
	#var particles = PbaParticleSystem.new()
	#print(particles.get_positions())
	PBAPhysicsServer.step(1)
