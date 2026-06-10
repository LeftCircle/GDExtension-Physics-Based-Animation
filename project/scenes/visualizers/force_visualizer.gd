extends Node
class_name ForceVisualizer


@export var force :PBAForce
@export var indices : Array[int]
@export var particle_system : PBAParticleSystem
@export var arrow_thickness : float = 0.05


func _ready() -> void:
	# Spawn in n arrows for each indice
	for i in range(indices.size()):
		var arrow := Arrow3D.new()
		arrow.opposite_direction = true
		arrow.arrow_thickness = arrow_thickness
		add_child(arrow)

func _physics_process(delta: float) -> void:
	var acc = force.get_accelerations(particle_system)
	#for i in range(positions.size()):
	#	$"../Visualizers/VectorVisualizer".draw(positions[i], positions[i] + acc[i])
	var positions := particle_system.get_positions()
	for i in range(indices.size()):
		var arrow : Arrow3D = get_child(i)
		arrow.global_position = positions[indices[i]]
		arrow.arrow_size = acc[indices[i]].length()
		arrow.look_at(arrow.global_position + acc[indices[i]])
