#pragma once

#include <vector>

#include "godot_cpp/classes/resource.hpp"
#include "godot_cpp/variant/vector3.hpp"
#include "godot_cpp/variant/aabb.hpp"

#include "partial_solvers.h"
#include "GISolver.h"
#include "sph_solver.h"
#include "rbd_solvers.h"
#include "boid_solvers.h"
#include "occupancy_volume.h"
#include "AABB.h"
#include "sph_kernel.h"

#include "pba_helpers.h"
#include "pba_particle_system.h"
#include "pba_physics_server.h"
#include "pba_forces.h"



using namespace godot;


class PBASolver : public Resource{
    GDCLASS(PBASolver, Resource)

public:
    enum IntegratorType {
        FORWARD,
        BACKWARD,
        LEAP_FROG,
        SIXTH_ORDER
    };

    enum SolverType {
        PARTICLE,
        SOFT_BODY,
        SPH,
        BOID,
        RIGID_BODY
    };
protected:
    static void _bind_methods();
    
    std::shared_ptr<pba::GISolverSystem> _solver_system;
    double _dt = 0.0166667;
    pba::idx_volume_sp _occupancy_volume;

    void _compose(pba::GISolver_sp a, pba::GISolver_sp b, IntegratorType integ);
    TypedArray<PBAForce> _forces;
    

public:
    void build(
        PBAParticleSystem* ps,
        SolverType st,
        IntegratorType integ,
        double dt,
        TypedArray<PBAForce> forces,
        AABB bounds = AABB(Vector3(0, 0, 0), Vector3(0, 0, 0)),
        double cell_size = 1.0
    );

    void solve();

    void set_forces(const TypedArray<PBAForce> &forces) { _forces = forces; }
    TypedArray<PBAForce> get_forces() { return _forces; }
};

VARIANT_ENUM_CAST(PBASolver::IntegratorType);
VARIANT_ENUM_CAST(PBASolver::SolverType);



