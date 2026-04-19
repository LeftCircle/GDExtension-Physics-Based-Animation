#include "pba_particle_system.h"


void PBAParticleSystem::_bind_methods() {
	godot::ClassDB::bind_method(D_METHOD("get_positions"), &PBAParticleSystem::get_positions);
}

void PBAParticleSystem::_physics_process(double delta){
    
}

void PBAParticleSystem::create(TYPE type, int n_particles){
    switch (type){
        case PARTICLES:
            _dsd = std::make_shared<pba::DynamicalStateData>();
            break;
        case SOFT_BODY:
            _dsd = std::make_shared<pba::SoftBody>();
            break;
        case RIGID_BODY:
            _dsd = std::make_shared<pba::RigidBodyStateData>();
            break;
        case SPH:
            _dsd = std::make_shared<pba::SPHData>();
            break;
        case BOIDS:
            _dsd = std::make_shared<pba::BoidStateData>();
            break;
    }
    _dsd->add(n_particles);
}

PackedVector3Array PBAParticleSystem::get_positions() const {
    PackedVector3Array positions;

    return positions;
}