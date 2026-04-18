#include "pba_forces.h"



void PBAForceSystem::_bind_methods(){
    godot::ClassDB::bind_method(
        D_METHOD("add_gravity", "gravity"),
        &PBAForceSystem::add_gravity
    );
}

void PBAForceSystem::add_gravity(Vector3 g){
    pba::Vector _g = gvtpba(g);
    std::shared_ptr<pba::SimpleGravityForce> grav = std::make_shared<pba::SimpleGravityForce>(_g);
    _force_system->add_force(grav);
}

