#pragma once

#include "godot_cpp/classes/node3d.hpp"
#include "godot_cpp/variant/vector3.hpp"
#include "godot_cpp/classes/ref_counted.hpp"

#include "collision_object.h"
#include "collision_surface.h"
#include "pba_helpers.h"

using namespace godot;

class PBACollisionObject : public Node3D {
    GDCLASS(PBACollisionObject, Node3D)
 
protected:
    static void _bind_methods() {};
    std::shared_ptr<pba::CollisionObject> _co;

public:
    const pba::CollisionObject_sp get_collision_object() { return _co; }
};

class PBACollisionSurface : public RefCounted{
    GDCLASS(PBACollisionSurface, RefCounted)

protected:
    static void _bind_methods();
    std::shared_ptr<pba::CollisionSurface> _cs;

public:
    const pba::CollisionSurface_sp get_surface() const noexcept { return _cs; }
    void register_collision_object(PBACollisionObject* co);
};

class PBACollisionPlane : public PBACollisionObject {
    GDCLASS(PBACollisionPlane, Node3D)

protected:
    static void _bind_methods();

public:
    void init(Vector3 point_on_plane, Vector3 normal);
};






