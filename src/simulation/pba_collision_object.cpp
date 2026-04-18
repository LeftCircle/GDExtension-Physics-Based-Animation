#include "pba_collision_object.h"


void PBACollisionSurface::_bind_methods() {
	godot::ClassDB::bind_method(
        D_METHOD("register_collision_object", "PBACollisionObject"),
        &PBACollisionSurface::register_collision_object
    );
}

void PBACollisionPlane::_bind_methods() {
    godot::ClassDB::bind_method(
       D_METHOD("init", "point_on_plane", "normal"),
       &PBACollisionPlane::init 
    );
}

void PBACollisionSurface::register_collision_object(PBACollisionObject* co){
    _cs->add_collision_object(co->get_collision_object());
}

void PBACollisionPlane::init(Vector3 point_on_plane, Vector3 normal){

    _co = std::make_shared<pba::CollisionPlane>(
        godot_vec_to_pba(point_on_plane),
        godot_vec_to_pba(point_on_plane));
}



