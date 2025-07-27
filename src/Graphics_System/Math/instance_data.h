#pragma once

#include "vector4D.h"
#include "vector3D.h"
#include "vector2D.h"

class Instance_Data {
public:
    Instance_Data() : pos(),uv(),atlas_offset(),edge_mask((UINT)0U), decal_uv()
    {};
    Instance_Data(Vector3D position, Vector2D UV, Vector2D Atlas) : pos(position),uv(UV), atlas_offset(Atlas),edge_mask((UINT)0U), decal_uv()
    {};
    Instance_Data(const Instance_Data &inst) : pos(inst.pos),uv(inst.uv),atlas_offset(inst.atlas_offset),edge_mask(inst.edge_mask), decal_uv(inst.decal_uv)
    {};
    ~Instance_Data() {};

    Vector3D pos;
    Vector2D uv;
    Vector2D atlas_offset;
    Vector2D decal_uv;
    UINT edge_mask;
};