#include "pba_particle_system.h"


void PBAParticleSystem::_bind_methods() {
	godot::ClassDB::bind_method(D_METHOD("get_positions"), &PBAParticleSystem::get_positions);
}

void PBAParticleSystem::_physics_process(double delta){
    
}


PackedVector3Array PBAParticleSystem::get_positions() const {
    PackedVector3Array positions;

    return positions;
}