#pragma once

#include <algorithm>

#include "godot_cpp/classes/node3d.hpp"

#include "dynamical_state_data.h"
#include "soft_body_data.h"
#include "sph_data.h"
#include "rigid_body.h"
#include "boids_state_data.h"
#include "shapes.h"

#include "pba_resources.h"
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
    void _validate_property(PropertyInfo &p_property) const;
    
    TYPE _type = PARTICLES;
    
public:
    TYPE get_type() const noexcept { return _type; }
    PackedVector3Array get_positions() const;
    pba::DSD_sp get_dsd() { return _dsd; }
    TypedArray<PBASoftTriangle> get_soft_triangles() { return soft_triangles; }
    TypedArray<PBAEdge> get_edges() { return edges; }
    
    void set_type(TYPE t) noexcept;
    void set_soft_triangles(TypedArray<PBASoftTriangle> new_soft_triangles) { soft_triangles = new_soft_triangles; }
    void set_edges(TypedArray<PBAEdge> new_edges) { edges = new_edges; }
    
    void _ready() override;
    
    void add_particle(Vector3 pos);
    void set_position(int i, Vector3 pos);
    void create(TYPE tpye, int particle_count);
    void sync_soft_triangles_at_runtime();
    void runtime_sync();

    TypedArray<PBASoftTriangle> soft_triangles;
    TypedArray<PBAEdge> edges;

protected:
    void _sync_edges_at_runtime();
};

VARIANT_ENUM_CAST(PBAParticleSystem::TYPE);
