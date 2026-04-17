#include "pba_particle_system.h"


void PbaParticleSystem::_bind_methods() {
	godot::ClassDB::bind_method(D_METHOD("get_positions"), &PbaParticleSystem::get_positions);
}

void PbaParticleSystem::_physics_process(double delta){
    
}


PackedVector3Array PbaParticleSystem::get_positions() const {
    PackedVector3Array positions;

    return positions;
}