extends Node3D
class_name VectorVisualizer

@onready var mesh = $Pivot/MeshInstance3D.mesh
@onready var multi_mesh = $Node/MultiMeshInstance3D

func clear() -> void:
	mesh.clear_surfaces();

func draw(p0 : Vector3, p1 : Vector3) -> void:
	return
	mesh.surface_begin(Mesh.PRIMITIVE_LINES)
	mesh.surface_add_vertex(p0)
	mesh.surface_add_vertex(p1)
	mesh.surface_end()

func size_multimesh(size : int):
	#mesh.multimesh.instance_count = positions.size()
	multi_mesh.multimesh.instance_count = size

func draw_multi_mesh(p0 : Vector3, p1 : Vector3, idx : int):
	var b = Basis()
	b = b.scaled(Vector3(1.0, 1.0, p0.distance_to(p1)))
	b = b.rotated(Vector3(1, 0, 0), -PI / 2.0)
	var t = Transform3D(b, p0) 
	#t = t.translated((p0 - p1) / 2.0)
	t = t.scaled(Vector3(1.0, 1.0, p0.distance_to(p1)))
	t = t.looking_at(p1)
	t = t.rotated_local(Vector3(1, 0, 0), -PI / 2.0)
	multi_mesh.multimesh.set_instance_transform(idx, t)
	
	#var t = Transform3D(Basis(), positions[i])
	#mesh.multimesh.set_instance_transform(i, t)
	

func draw_arrow(p0 : Vector3, p1 : Vector3) -> void:
	global_position = p0
	look_at(p1)
	$Pivot/Body.mesh.height = p0.distance_to(p1)
	$Pivot/Body.global_position = p0 + (p1 - p0) / 2.0
	$Pivot/HeadStart.global_position = p1
	$Arrow3D.global_position = p0
	$Arrow3D.arrow_size = p0.distance_to(p1)
	
