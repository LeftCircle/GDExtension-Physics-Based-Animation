extends PBAParticleSystem
class_name PBA_MultiMeshParticles

@onready var mesh: MultiMeshInstance3D = $MultiMeshInstance3D

func _ready() -> void:
	var solver := PBASolver.new()
	create(get_type(), 1)
	solver.build(self,
		PBASolver.SolverType.PARTICLE,
		PBASolver.IntegratorType.LEAP_FROG,
		0.016667,
		AABB(Vector3(0, 0, 0), Vector3(0, 0, 0)),
		1
	)

func _physics_process(delta):
	var positions = get_positions()
	mesh.multimesh.instance_count = positions.size()
	for i in positions.size():
		var t = Transform3D(Basis(), positions[i])
		mesh.multimesh.set_instance_transform(i, t)
