#pragma once

#include <memory>

#include "godot_cpp/classes/resource.hpp"
#include "godot_cpp/variant/vector3.hpp"

#include "force.h"
#include "force_library.h"
#include "pba_helpers.h"
#include "pba_particle_system.h"

using namespace godot;

class PBAForceSystem : public Resource{
    GDCLASS(PBAForceSystem, Resource)

protected:
    static void _bind_methods();
    pba::ForceSystem_sp _force_system = std::make_shared<pba::ForceSystem>();

public:
    pba::ForceSystem_sp get_force_system() const { return _force_system; }
    void add_gravity(Vector3 g);

};


class PBAForce : public Resource{
    GDCLASS(PBAForce, Resource)

public:
    enum TYPE{
        SOFT_TRIANGLE
    };

protected:
    static void _bind_methods();

    TYPE _type;

public:
    TYPE get_type() const noexcept { return _type; }
    void set_type(TYPE t) noexcept { _type = t; }

    pba::Force_sp get_pba_force() const;
    TypedArray<godot::Vector3> get_accelerations(PBAParticleSystem* ps) const;
};

VARIANT_ENUM_CAST(PBAForce::TYPE);