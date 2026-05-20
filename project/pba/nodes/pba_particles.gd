extends PBAParticleSystem
class_name PBA_MultiMeshParticles

@onready var mesh: MultiMeshInstance3D = $MultiMeshInstance3D
@export var initial_particle_container : Node3D
@export var forces_to_add : Array[PBAForce]

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

func _physics_process(delta):
	var positions = get_positions()
	mesh.multimesh.instance_count = positions.size()
	for i in positions.size():
		var t = Transform3D(Basis(), positions[i])
		mesh.multimesh.set_instance_transform(i, t)


func _add_initial_particles() -> void:
	var particles = initial_particle_container.get_children()
	for p : Node3D in particles:
		add_particle(p.global_position)
		p.queue_free()
