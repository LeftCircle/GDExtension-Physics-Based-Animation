#pragma once

#include <vector>

#include <godot_cpp/core/class_db.hpp>
#include "godot_cpp/classes/node.hpp"

#include "force.h"
#include "partial_solvers.h"
#include "dynamical_state_data_base.h"
#include "collision_surface.h"
#include "collision_handler.h"
#include "pba_collision_object.h"
#include "GISolver.h"
#include "rbd_solvers.h"

using namespace godot;


class PBAPhysicsServer : public Node{
    GDCLASS(PBAPhysicsServer, Node)

    static PBAPhysicsServer* singleton;

protected:
    static void _bind_methods();
    
    std::vector<std::shared_ptr<pba::GISolverSystem>> _solvers;
    
public:
    static PBAPhysicsServer* get_singleton();
    pba::CollisionHandler_sp collision_handler = std::make_shared<pba::CollisionHandler>();
    std::shared_ptr<pba::RBDCollisionHandler> rbd_collision_handler = std::make_shared<pba::RBDCollisionHandler>();

    PBAPhysicsServer();
    ~PBAPhysicsServer();

   // void _physics_process(double delta) override;

    void step(double delta);
    void register_collision_surface(PBACollisionSurface* cs) {
        collision_handler->register_collision_surface(cs->get_surface());
        rbd_collision_handler->register_collision_surface(cs->get_surface());
    }

    // TO DO -> also delete unused solvers
    void register_solver(std::shared_ptr<pba::GISolverSystem> solver) { _solvers.push_back(solver); }
};