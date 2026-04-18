#pragma once

#include <vector>

#include <godot_cpp/core/class_db.hpp>
#include "godot_cpp/classes/object.hpp"

#include "force.h"
#include "partial_solvers.h"
#include "dynamical_state_data_base.h"
#include "collision_surface.h"
#include "collision_handler.h"
#include "pba_collision_object.h"
#include "GISolver.h"

using namespace godot;



class PBAPhysicsServer : public Object{
    GDCLASS(PBAPhysicsServer, Object)

    static PBAPhysicsServer* singleton;

protected:
    static void _bind_methods();
    // We need a map for each particle system to the solvers that drive them
    
    
    
public:
    static PBAPhysicsServer* get_singleton();
    pba::CollisionHandler_sp collision_handler = std::make_shared<pba::CollisionHandler>();

    PBAPhysicsServer();
    ~PBAPhysicsServer();

    void step(double delta);
    void register_collision_surface(PBACollisionSurface* cs) {
        _coll_handler->register_collision_surface(cs->get_surface()); 
    }

    void add_particle_system();

};