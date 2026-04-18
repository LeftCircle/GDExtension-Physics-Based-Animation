#include "pba_solvers.h"



void PBAAdvancePositionSolver::_bind_methods() {
	godot::ClassDB::bind_method(
        D_METHOD("init", "PBAParticleSystem"),
        &PBAAdvancePositionSolver::init
    );
}

void PBAAdvancePositionSolver::init(PBAParticleSystem* ps){
    pba::CollisionHandler_sp ch = PBAPhysicsServer::get_singleton()->collision_handler;
    _solver = std::make_shared<pba::PartialSolverAdvancePosition>(ps->get_dsd(), ch);
}

void PBAAdvanceVelocityWithForces::_bind_methods() {
    godot::ClassDB::bind_method(
        D_METHOD("init", "PBAParticles", "PBAForceSystem"),
        &PBAAdvanceVelocityWithForces::init
    );
}

void PBAAdvanceVelocityWithForces::init(PBAParticleSystem* ps, PBAForceSystem* fs){
    _solver = std::make_shared<pba::AdvanceVelocityWithForces>(ps->get_dsd(), fs->get_force_system());
}