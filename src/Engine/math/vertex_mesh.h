#pragma once

#include "vector3D.h"
#include "vector2D.h"

class Vertex_Mesh {
public:
    Vertex_Mesh() : pos(),uv(),normal()
    {};
    Vertex_Mesh(Vector3D position, Vector2D UV, Vector3D Normal) : pos(position),uv(UV),normal(Normal)
    {};
    Vertex_Mesh(const Vertex_Mesh &vect) : pos(vect.pos),uv(vect.uv),normal(vect.normal)
    {};
    ~Vertex_Mesh() {};

    Vector3D pos;
    Vector2D uv;
    Vector3D normal;
};