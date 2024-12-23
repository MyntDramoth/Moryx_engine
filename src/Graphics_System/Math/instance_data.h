#pragma once

#include "vector3D.h"
#include "vector2D.h"

class Instance_Data {
public:
    Instance_Data() : pos(),uv()
    {};
    Instance_Data(Vector3D position, Vector2D UV) : pos(position),uv(UV)
    {};
    Instance_Data(const Instance_Data &vect) : pos(vect.pos),uv(vect.uv)
    {};
    ~Instance_Data() {};

    Vector3D pos;
    Vector2D uv;
 
};