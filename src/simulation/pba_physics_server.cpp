#include "pba_physics_server.h"


PBAPhysicsServer* PBAPhysicsServer::singleton = nullptr;

PBAPhysicsServer* PBAPhysicsServer::get_singleton(){
    return singleton;
}

PBAPhysicsServer::PBAPhysicsServer() {
    ERR_FAIL_COND(singleton != nullptr);
    // memory management handled by godot in register_types
    singleton = this;
}

PBAPhysicsServer::~PBAPhysicsServer() {
    ERR_FAIL_COND(singleton != this);
    singleton = nullptr;
}

void PBAPhysicsServer::_bind_methods() {
    ClassDB::bind_method(D_METHOD("step", "delta"), &PBAPhysicsServer::step);
    ClassDB::bind_method(
        D_METHOD("register_collision_surfaced", "collision_surface"),
        &PBAPhysicsServer::register_collision_surface
    );
}

void PBAPhysicsServer::step(double delta) {
    for(auto solver : _solvers){
        solver->solve(delta);
    }
}

