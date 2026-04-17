extends Node


func _ready() -> void:
	var example := ExampleClass.new()
	example.print_type(example)
	var particles = PbaParticleSystem.new()
	print(particles.get_positions())

## Multi mesh instance for particle sims
# example.gd
#@onready var mesh: MultiMeshInstance3D = $MultiMeshInstance3D
#func _physics_process(delta):
#    # sim auto-steps internally
#    var positions = sim.get_positions()
#    mesh.multimesh.instance_count = positions.size()
#    for i in positions.size():
#        var t = Transform3D(Basis(), positions[i])
#        mesh.multimesh.set_instance_transform(i, t)
