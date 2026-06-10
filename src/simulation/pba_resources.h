#pragma once


#include "godot_cpp/classes/resource.hpp"
#include "godot_cpp/variant/vector3.hpp"
#include "godot_cpp/variant/vector3i.hpp"

#include "soft_edge.h"
#include "pba_helpers.h"

using namespace godot;

class PBASoftTriangle : public Resource{
    GDCLASS(PBASoftTriangle, Resource)

protected:
    static void _bind_methods();
    Vector3i _idxs;

    double _area;
    double _k;


public:
    void set_idxs(Vector3i idxs) {_idxs = idxs; }
    Vector3i get_idxs() { return _idxs; }
    
    void set_area(double area) { _area = area; }
    double get_area() { return _area; }

    void set_spring_constant(double k) { _k = k; }
    double get_k() { return _k; }
};

class PBAEdge : public Resource{
    GDCLASS(PBAEdge, Resource)

protected:
    static void _bind_methods();
    Vector2i _idxs;
    float _rest_length;
    double _k;

public:
    void set_idxs(Vector2i idxs) {_idxs = idxs; }
    Vector2i get_idxs() { return _idxs; }
    
    void set_rest_length(double rl) { _rest_length = rl; }
    double get_rest_length() { return _rest_length; }

    void set_spring_constant(double k) { _k = k; }
    double get_k() { return _k; }
};





