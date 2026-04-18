#pragma once

#include "godot_cpp/variant/vector3.hpp"


#include "Vector.h"



static pba::Vector inline godot_vec_to_pba(godot::Vector3 v){ return pba::Vector(v.x, v.y, v.z); }
static pba::Vector inline gvtpba(godot::Vector3 v) { return pba::Vector(v.x, v.y, v.z); }