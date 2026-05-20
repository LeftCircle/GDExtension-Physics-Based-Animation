#include "pba_resources.h"



void PBASoftTriangle::_bind_methods() {
	godot::ClassDB::bind_method(D_METHOD("get_idxs"), &PBASoftTriangle::get_idxs);
    godot::ClassDB::bind_method(D_METHOD("set_idxs", "idxs"), &PBASoftTriangle::set_idxs);
    
	godot::ClassDB::bind_method(D_METHOD("get_area"), &PBASoftTriangle::get_area);
    godot::ClassDB::bind_method(D_METHOD("set_area", "area"), &PBASoftTriangle::set_area);
    
	godot::ClassDB::bind_method(D_METHOD("get_k"), &PBASoftTriangle::get_k);
    godot::ClassDB::bind_method(D_METHOD("set_spring_constant", "k"), &PBASoftTriangle::set_spring_constant);


    ADD_PROPERTY(PropertyInfo(Variant::VECTOR3I, "idxs"), "set_idxs", "get_idxs");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "rest_area"), "set_area", "get_area");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "spring_constant"), "set_spring_constant", "get_k");
}



