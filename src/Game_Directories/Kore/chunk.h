#pragma once

#include "../../Graphics_System/Math/vector3D.h"

class Chunk{
public:
    Chunk() {};
    ~Chunk() {};

    unsigned int chunk_data[32][32][32] = {0};
    Vector3D chunk_pos;
};