#pragma once

#include "vector3D.h"
#include "vector2D.h"

class Vertex_Mesh {
public:
    Vertex_Mesh() : pos(),uv(),normal(),tangent(),binormal()
    {};
    Vertex_Mesh(const Vector3D &position,const Vector2D &UV,const Vector3D &Normal,const Vector3D &Tangent,const Vector3D &BiNormal) : pos(position),uv(UV),normal(Normal),tangent(Tangent),binormal(BiNormal)
    {};
    Vertex_Mesh(const Vertex_Mesh &vect) : pos(vect.pos),uv(vect.uv),normal(vect.normal),tangent(vect.tangent),binormal(vect.binormal)
    {};
    ~Vertex_Mesh() {};

    Vector3D pos;
    Vector2D uv;
    Vector3D normal;
    Vector3D tangent;
    Vector3D binormal;
};