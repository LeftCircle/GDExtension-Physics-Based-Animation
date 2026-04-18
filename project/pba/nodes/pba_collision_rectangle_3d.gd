extends Node3D

@export var shape : BoxShape3D = BoxShape3D.new()
@export var inward_normals = false

var cs := PBACollisionSurface.new()

func _ready() -> void:
	# Just start by registering the collision shape
	# For now let's do 3 planes
	
	var p = global_position
	var top_plane_p = p + Vector3(0, shape.size.y / 2, 0)
	var right_plane_p = p + Vector3(shape.size.x / 2, 0, 0)
	var left_plane_p = p + Vector3(-shape.size.x / 2, 0, 0)
	var back_plane_p = p + Vector3(0, 0, shape.size.z / 2)
	var front_plane_p = p + Vector3(0, 0, -shape.size.z / 2)
	var bottom_plane_p = p + Vector3(0, -shape.size.y / 2, 0)
	var ns = -1 if inward_normals else 1
	var top_p = PBACollisionPlane.new()
	var r_p = PBACollisionPlane.new()
	var l_p = PBACollisionPlane.new()
	var f_p = PBACollisionPlane.new()
	var back_p = PBACollisionPlane.new()
	var bottom_p = PBACollisionPlane.new()
	top_p.init(top_plane_p, Vector3.UP * ns)
	r_p.init(right_plane_p, Vector3.RIGHT * ns)
	l_p.init(left_plane_p, Vector3.LEFT * ns)
	f_p.init(top_plane_p, Vector3.FORWARD * ns)
	back_p.init(top_plane_p, Vector3.BACK * ns)
	bottom_p.init(top_plane_p, Vector3.DOWN * ns)
	cs.register_collision_object(top_p)
	cs.register_collision_object(r_p)
	cs.register_collision_object(l_p)
	cs.register_collision_object(f_p)
	cs.register_collision_object(back_p)
	cs.register_collision_object(bottom_p)
	
	
