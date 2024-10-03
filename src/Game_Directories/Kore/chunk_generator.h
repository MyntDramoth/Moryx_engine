#pragma once
#include "../../Graphics_System/Math/vector3D.h"
#include "chunk.h"
#include "voxel_data.h"


class Chunk_Generator
{
public:
    Chunk_Generator();
    ~Chunk_Generator();

    void marching_cubes_generator(unsigned int size);
    void noise_gen(Vector3D pos);
    void greedy_mesh(Vector3D pos);

private:
    Chunk chunk;
    
};