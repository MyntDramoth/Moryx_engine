#pragma once
#include "../Graphics_System/Math/vector3D.h"


class AABB {
public:
    Vector3D bounds;
    Vector3D position;
    AABB() : position({0.0f,0.0f,0.0f}), bounds({0.0f,0.0f,0.0f}) {};
    AABB( Vector3D pos, Vector3D boundries) : position(pos), bounds(boundries) {};

    bool contains(Vector3D point)
    {
        return (point.x >= position.x - bounds.x && point.x <= position.x + bounds.x) &&
               (point.y >= position.y - bounds.y && point.y <= position.y + bounds.y) &&
               (point.z >= position.z - bounds.z && point.z <= position.z + bounds.z);
    }

    bool intersects(AABB other)
    {
        return (position.x - bounds.x < other.position.x + other.bounds.x &&
                position.x + bounds.x > other.position.x - other.bounds.x &&
                position.y - bounds.y < other.position.y + other.bounds.y &&
                position.y + bounds.y > other.position.y - other.bounds.y &&
                position.z - bounds.z < other.position.z + other.bounds.z &&
                position.z + bounds.z > other.position.z - other.bounds.z);
    }
};