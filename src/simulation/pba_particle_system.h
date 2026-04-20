#pragma once

#include <algorithm>

#include "godot_cpp/classes/node3d.hpp"

#include "dynamical_state_data.h"
#include "soft_body_data.h"
#include "sph_data.h"
#include "rigid_body.h"
#include "boids_state_data.h"

#include "pba_helpers.h"

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

    TYPE _type = PARTICLES;

public:
    void set_type(TYPE t) noexcept { _type = t; }
    TYPE get_type() const noexcept { return _type; }
    
    void _ready() override;
    
    void create(TYPE tpye, int particle_count);
    void add_particle(Vector3 pos);

    PackedVector3Array get_positions() const;
    
    pba::DSD_sp get_dsd() { return _dsd; }
};

VARIANT_ENUM_CAST(PBAParticleSystem::TYPE);
