#pragma once

#include "vector3D.h"
#include "vector2D.h"

class Vertex_Mesh {
public:
    Vertex_Mesh() : pos(),uv() 
    {};
    Vertex_Mesh(Vector3D position, Vector2D UV) : pos(position),uv(UV) 
    {};
    Vertex_Mesh(const Vertex_Mesh &vect) : pos(vect.pos),uv(vect.uv) 
    {};
    ~Vertex_Mesh() {};

    Vector3D pos;
    Vector2D uv;
};