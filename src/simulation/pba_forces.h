#pragma once


#include "godot_cpp/classes/resource.hpp"
#include "godot_cpp/variant/vector3.hpp"

#include "force.h"
#include "force_library.h"
#include "pba_helpers.h"

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