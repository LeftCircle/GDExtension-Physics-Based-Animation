extends Node3D
class_name VectorVisualizer

@onready var mesh = $MeshInstance3D.mesh

func clear() -> void:
	mesh.clear_surfaces();

func draw(p0 : Vector3, p1 : Vector3) -> void:
	mesh.surface_begin(Mesh.PRIMITIVE_LINES)
	mesh.surface_add_vertex(p0)
	mesh.surface_add_vertex(p1)
	mesh.surface_end()
