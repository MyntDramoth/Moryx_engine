#pragma once

#include "../../Graphics_System/prerequisites.h"


enum Voxel_Type {
    AIR,
    STONE,
    DIRT,
    GRASS,
    ICE
};

struct Voxel_data {
    Voxel_Type type;
    mesh_sptr voxel_mesh;
};