#pragma once

#include "entity.h"
#include <set>

class System
{
public:
	std::set<entity> entities;
    std::set<voxel> voxels;
};