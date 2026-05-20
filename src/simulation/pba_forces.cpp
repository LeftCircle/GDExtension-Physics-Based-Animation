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

void PBAForce::_bind_methods(){
    godot::ClassDB::bind_method(D_METHOD("get_type"), &PBAForce::get_type);
    godot::ClassDB::bind_method(D_METHOD("set_type", "type"), &PBAForce::set_type);

    BIND_ENUM_CONSTANT(SOFT_TRIANGLE)

    ADD_PROPERTY(PropertyInfo(Variant::INT, "type", PROPERTY_HINT_ENUM, "Soft Triangle"), "set_type", "get_type");


}

pba::Force_sp PBAForce::get_pba_force(){
    switch (_type){
        case SOFT_TRIANGLE:{
            return std::make_shared<pba::SoftTriangleForce>();
        }
    }
}