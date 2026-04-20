#include "pba_particle_system.h"


void PBAParticleSystem::_bind_methods() {
	godot::ClassDB::bind_method(D_METHOD("get_positions"), &PBAParticleSystem::get_positions);
    godot::ClassDB::bind_method(D_METHOD("add_particle", "position"), &PBAParticleSystem::add_particle);
    godot::ClassDB::bind_method(D_METHOD("create", "solver type", "n_particles"), &PBAParticleSystem::create);

    ClassDB::bind_method(D_METHOD("set_type", "type"), &PBAParticleSystem::set_type);
    ClassDB::bind_method(D_METHOD("get_type"), &PBAParticleSystem::get_type);

    BIND_ENUM_CONSTANT(PARTICLES);
    BIND_ENUM_CONSTANT(SOFT_BODY);
    BIND_ENUM_CONSTANT(RIGID_BODY);
    BIND_ENUM_CONSTANT(SPH);
    BIND_ENUM_CONSTANT(BOIDS);

    ADD_PROPERTY(PropertyInfo(Variant::INT, "type", PROPERTY_HINT_ENUM, "Particles,Soft Body,Rigid Body,SPH,Boids"), "set_type", "get_type");
}

void PBAParticleSystem::_ready(){
    create(_type, 1);
    printf("Create called during parent ready\n");
}

void PBAParticleSystem::create(TYPE type, int n_particles){
    switch (type){
        case PARTICLES:{
            _dsd = std::make_shared<pba::DynamicalStateData>();
            break;
        }
        case SOFT_BODY:{
            _dsd = std::make_shared<pba::SoftBody>();
            break;
        }
        case RIGID_BODY:{
            _dsd = std::make_shared<pba::RigidBodyStateData>();
            break;
        }
        case SPH:{
            _dsd = std::make_shared<pba::SPHData>();
            break;
        }
        case BOIDS:{
            _dsd = std::make_shared<pba::BoidStateData>();
            break;
        }
    }
    _dsd->add(n_particles);
}

void PBAParticleSystem::add_particle(Vector3 pos){
    _dsd->add();
    _dsd->set_position(_dsd->n_particles() - 1, gvtpba(pos));
}

PackedVector3Array PBAParticleSystem::get_positions() const {
    PackedVector3Array positions;
    if (!_dsd) return positions;
    positions.resize(_dsd->n_particles());
    auto pos = _dsd->get_vector_attribute_span("positions");
    std::transform(pos.begin(), pos.end(), positions.begin(), pbavtg);
    return positions;
}