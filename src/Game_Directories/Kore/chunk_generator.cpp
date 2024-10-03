#include "chunk_generator.h"

#include <FastNoise/FastNoise.h>

Chunk_Generator::Chunk_Generator()
{

}

Chunk_Generator::~Chunk_Generator()
{

}

void Chunk_Generator::marching_cubes_generator(unsigned int size) {
    for (int x = 0; x < size; x++) {
        for (int y = 0; y < size; y++) {
            for (int z = 0; z < size; z++) {
                noise_gen({(float)x,(float)y,(float)z});
            }
        }
    }

    // for (int x = 0; x < size; x++) {
    //     for (int y = 0; y < size; y++) {
    //         for (int z = 0; z < size; z++) {
    //             greedy_mesh({(float)x,(float)y,(float)z});
    //         }
    //     }
    // }
}

void Chunk_Generator::noise_gen(Vector3D pos) {
    int seed = 5098;
    auto cell = FastNoise::New<FastNoise::CellularDistance>();
    auto res = cell.get()->GenSingle3D((unsigned int)pos.x,(unsigned int)pos.y,(unsigned int)pos.z,seed);
    //MORYX_INFO("Noise Val: " << res);
   // chunk.chunk_data[(unsigned int)pos.x][(unsigned int)pos.y][(unsigned int)pos.z] = Voxel_Type::AIR;

    //chunk.chunk_data[(unsigned int)pos.x][(unsigned int)pos.y][(unsigned int)pos.z] = Voxel_Type::STONE;
}

void Chunk_Generator::greedy_mesh(Vector3D pos) {

    if(chunk.chunk_data[(unsigned int)pos.x][(unsigned int)pos.y][(unsigned int)pos.z] != Voxel_Type::AIR) {

    }

}
