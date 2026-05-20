#include "pba_particle_system.h"


void PBAParticleSystem::_bind_methods() {
	godot::ClassDB::bind_method(D_METHOD("get_positions"), &PBAParticleSystem::get_positions);
    godot::ClassDB::bind_method(D_METHOD("add_particle", "position"), &PBAParticleSystem::add_particle);
    godot::ClassDB::bind_method(D_METHOD("create", "solver type", "n_particles"), &PBAParticleSystem::create);

    ClassDB::bind_method(D_METHOD("set_type", "type"), &PBAParticleSystem::set_type);
    ClassDB::bind_method(D_METHOD("get_type"), &PBAParticleSystem::get_type);
    ClassDB::bind_method(D_METHOD("set_soft_triangles", "soft_tris"), &PBAParticleSystem::set_soft_triangles);
    ClassDB::bind_method(D_METHOD("get_soft_triangles"), &PBAParticleSystem::get_soft_triangles);
    ClassDB::bind_method(D_METHOD("sync_soft_triangles_at_runtime"), &PBAParticleSystem::sync_soft_triangles_at_runtime);

    BIND_ENUM_CONSTANT(PARTICLES);
    BIND_ENUM_CONSTANT(SOFT_BODY);
    BIND_ENUM_CONSTANT(RIGID_BODY);
    BIND_ENUM_CONSTANT(SPH);
    BIND_ENUM_CONSTANT(BOIDS);

    ADD_PROPERTY(PropertyInfo(Variant::INT, "type", PROPERTY_HINT_ENUM, "Particles,Soft Body,Rigid Body,SPH,Boids"), "set_type", "get_type");
    ADD_PROPERTY(
        PropertyInfo(
            Variant::ARRAY,
            "soft_triangles",
            PROPERTY_HINT_ARRAY_TYPE,
            "PBASoftTriangle"
        ),
        "set_soft_triangles", "get_soft_triangles"
    );

}

void PBAParticleSystem::_validate_property(PropertyInfo &p_property) const {
    String name = p_property.name;
    // Test hiding the "mouse_filter" property from the editor.
    if (name == "soft_triangles" && _type != SOFT_BODY) {
        p_property.usage = PROPERTY_USAGE_NO_EDITOR;
    }
}

void PBAParticleSystem::set_type(TYPE t) noexcept {
    if (_type == t) return;
    _type = t;
    notify_property_list_changed();
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

void PBAParticleSystem::sync_soft_triangles_at_runtime() {
    auto sb = std::dynamic_pointer_cast<pba::SoftBody>(_dsd);
    if (!sb) return;

    sb->soft_triangles.clear();
    for (int i = 0; i < soft_triangles.size(); i++){
        Ref<PBASoftTriangle> tri = soft_triangles[i];
        double current_area = pba::Triangle::get_area(
            sb->p(tri->get_idxs()[0]),
            sb->p(tri->get_idxs()[1]),
            sb->p(tri->get_idxs()[2])
        );
        double area = tri->get_area() == 0 ? current_area : tri->get_area();
        sb->soft_triangles.emplace_back(
            tri->get_idxs()[0],
            tri->get_idxs()[1],
            tri->get_idxs()[2],
            area, 
            tri->get_k()
        );
    }
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