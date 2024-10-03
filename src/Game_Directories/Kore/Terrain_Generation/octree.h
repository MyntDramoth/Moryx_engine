#pragma once

#include "../../../Physics_System/AABB.h"
#include <vector>

class Octree
{
public:
    Octree();
    ~Octree();

    AABB aabb;

private:

};

 #include <optional>
class Octree_Node
{
public:

    AABB aabb;
    std::optional<uint64_t> vox_ID;
    Octree_Node* children[8];

    Octree_Node(AABB bounds) : aabb(bounds), vox_ID(std::nullopt) { for (int i = 0; i < 8; ++i){ children[i] = nullptr;}};
    ~Octree_Node( ) {for (int i = 0; i < 8; ++i){ delete children[i];}};

    bool is_leaf() const { return children[0] == nullptr; }


    void subdivide();
    void insert(const Vector3D& point, uint64_t id, int depth);
    uint64_t get_voxel(const Vector3D& point, int lod);
private:

};