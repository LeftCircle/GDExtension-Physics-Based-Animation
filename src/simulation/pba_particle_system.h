#pragma once

#include "godot_cpp/classes/node3d.hpp"
#include "dynamical_state_data.h"

using namespace godot;

class PbaParticleSystem : public Node3D {
    GDCLASS(PbaParticleSystem, Node3D)

protected:
    static void _bind_methods();
    pba::DSD_sp _dsd;

public:
    void _physics_process(double delta) override;
    // a bit unfortunate that we have to transform to godot vector types here
    PackedVector3Array get_positions() const;
};


