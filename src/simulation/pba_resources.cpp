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


void PBAEdge::_bind_methods() {
    godot::ClassDB::bind_method(D_METHOD("get_idxs"), &PBAEdge::get_idxs);
    godot::ClassDB::bind_method(D_METHOD("set_idxs", "idxs"), &PBAEdge::set_idxs);
    
    godot::ClassDB::bind_method(D_METHOD("set_rest_length", "rest_length"), &PBAEdge::set_rest_length);
    godot::ClassDB::bind_method(D_METHOD("get_rest_length"), &PBAEdge::get_rest_length);
    
    godot::ClassDB::bind_method(D_METHOD("get_k"), &PBAEdge::get_k);
    godot::ClassDB::bind_method(D_METHOD("set_spring_constant", "k"), &PBAEdge::set_spring_constant);


    ADD_PROPERTY(PropertyInfo(Variant::VECTOR2I, "idxs"), "set_idxs", "get_idxs");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "spring_constant"), "set_spring_constant", "get_k");
}
