extends PBAParticleSystem
class_name PBA_MultiMeshParticles

@onready var mesh: MultiMeshInstance3D = $MultiMeshInstance3D
@export var initial_particle_container : Node3D
@export var interaction_container : Node3D
@export var forces_to_add : Array[PBAForce]
@export var add_particle_selection : bool = true

static var _particle_to_solver : Dictionary = {
	PBAParticleSystem.TYPE.PARTICLES : PBASolver.SolverType.PARTICLE,
	PBAParticleSystem.TYPE.RIGID_BODY : PBASolver.SolverType.RIGID_BODY,
	PBAParticleSystem.TYPE.BOIDS : PBASolver.SolverType.BOID,
	PBAParticleSystem.TYPE.SOFT_BODY : PBASolver.SolverType.SOFT_BODY,
	PBAParticleSystem.TYPE.SPH : PBASolver.SolverType.SPH
}

func _ready() -> void:
	create(get_type(), 0)
	var solver := PBASolver.new()
	_add_initial_particles()
	if type == PBAParticleSystem.TYPE.SOFT_BODY:
		sync_soft_triangles_at_runtime()
	
	solver.build(self,
		_particle_to_solver[type],
		PBASolver.IntegratorType.LEAP_FROG,
		0.016667,
		forces_to_add,
		AABB(Vector3(0, 0, 0), Vector3(0, 0, 0)),
		1
	)
	if add_particle_selection:
		_add_particle_selection_nodes()

func _physics_process(delta):
	if PbaPhysicsServerDriver.is_physics_processing():
		_on_pba_physics_updates()
	else:
		_on_custom_update()

func _on_pba_physics_updates() -> void:
	var positions = get_positions()
	mesh.multimesh.instance_count = positions.size()
	for i in positions.size():
		var t = Transform3D(Basis(), positions[i])
		mesh.multimesh.set_instance_transform(i, t)
		if add_particle_selection:
			interaction_container.get_child(i).global_position = positions[i]

func _on_custom_update() -> void:
	for i in range(interaction_container.get_child_count()):
		var pos = interaction_container.get_child(i).global_position
		set_position(i, pos)
		var t = Transform3D(Basis(), pos)
		mesh.multimesh.set_instance_transform(i, t)

func _add_particle_selection_nodes() -> void:
	for i in range(get_positions().size()):
		var interaction = load("res://scenes/helpers/selectable_area3D.tscn").instantiate()
		interaction_container.add_child(interaction)

func _add_initial_particles() -> void:
	var particles = initial_particle_container.get_children()
	for p : Node3D in particles:
		add_particle(p.global_position)
		p.queue_free()
