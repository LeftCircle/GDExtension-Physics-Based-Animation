#pragma once


#include "godot_cpp/classes/resource.hpp"

#include "partial_solvers.h"
#include "GISolver.h"

#include "pba_particle_system.h"
#include "pba_physics_server.h"
#include "pba_forces.h"

using namespace godot;


class PBASolverBase : public Resource{
    GDCLASS(PBASolverBase, Resource)

protected:
    pba::GISolver_sp _solver;

public:
    pba::GISolver_sp get_solver() { return _solver; }  
};


class PBAAdvancePositionSolver : public PBASolverBase{
    GDCLASS(PBAAdvancePositionSolver, PBASolverBase)

protected:
    static void _bind_methods();

public:
    void init(PBAParticleSystem* particles);
};

class PBAAdvanceVelocityWithForces : public PBASolverBase{
    GDCLASS(PBAAdvanceVelocityWithForces, PBASolverBase)

protected:
    static void _bind_methods();
    
public:
    void init(PBAParticleSystem* particles, PBAForceSystem* force_system);
};



