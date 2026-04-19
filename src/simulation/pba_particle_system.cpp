#include "pba_particle_system.h"


void PBAParticleSystem::_bind_methods() {
	godot::ClassDB::bind_method(D_METHOD("get_positions"), &PBAParticleSystem::get_positions);
    godot::ClassDB::bind_method(D_METHOD("add_particle", "position"), &PBAParticleSystem::add_particle);
}

void PBAParticleSystem::_physics_process(double delta){}

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

void PBAParticleSystem::add_particle(Vector3 pos){
    _dsd->add();
    _dsd->set_position(_dsd->n_particles() - 1, gvtpba(pos));
}

PackedVector3Array PBAParticleSystem::get_positions() const {
    PackedVector3Array positions;
    positions.resize(_dsd->n_particles());
    auto pos = _dsd->get_vector_attribute_span("positions");
    std::transform(pos.begin(), pos.end(), positions.begin(), pbavtg);
    return positions;
}