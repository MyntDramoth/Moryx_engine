#pragma once

#include "vector4D.h"
#include "vector3D.h"
#include "vector2D.h"

class Instance_Data {
public:
    Instance_Data() : pos(),uv(),atlas_offset()
    {};
    Instance_Data(Vector3D position, Vector2D UV, Vector2D Atlas) : pos(position),uv(UV), atlas_offset(Atlas)
    {};
    Instance_Data(const Instance_Data &inst) : pos(inst.pos),uv(inst.uv),atlas_offset(inst.atlas_offset)
    {};
    ~Instance_Data() {};

    Vector3D pos;
    Vector2D uv;
    Vector2D atlas_offset;
};