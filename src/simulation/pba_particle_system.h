#pragma once

#include "godot_cpp/classes/node3d.hpp"
#include "dynamical_state_data.h"
#include "soft_body_data.h"
#include "sph_data.h"
#include "rigid_body.h"
#include "boids_state_data.h"

using namespace godot;

class PBAParticleSystem : public Node3D {
    GDCLASS(PBAParticleSystem, Node3D)

public:
    enum TYPE{
        PARTICLES,
        SOFT_BODY,
        RIGID_BODY,
        SPH,
        BOIDS
    };

protected:
    static void _bind_methods();
    pba::DSD_sp _dsd;

public:

    void create(TYPE tpye, int particle_count);

    void _physics_process(double delta) override;
    // a bit unfortunate that we have to transform to godot vector types here
    PackedVector3Array get_positions() const;
    
    pba::DSD_sp get_dsd() { return _dsd; }
};

VARIANT_ENUM_CAST(PBAParticleSystem::TYPE);
