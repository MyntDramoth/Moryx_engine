#include "octree.h"

Octree::Octree()
{

}

Octree::~Octree()
{

}

void Octree_Node::subdivide() {
    
    Vector3D child_bounds = aabb.bounds * 0.5f;

    for (int i = 0; i < 8; ++i) {
        Vector3D offset(
            (i & 1) ? child_bounds.x : -child_bounds.x,
            (i & 2) ? child_bounds.y : -child_bounds.y,
            (i & 4) ? child_bounds.z : -child_bounds.z
        );
        children[i] = new Octree_Node(AABB(aabb.position + offset, child_bounds));
    }

}

void Octree_Node::insert(const Vector3D &point, uint64_t id, int depth) {
    if (!aabb.contains(point)) {return;}

        if (depth == 0) {
            vox_ID = id;
            return;
        }

        if (is_leaf()) {
            subdivide();
        }

        for (int i = 0; i < 8; ++i) {
            children[i]->insert(point, id, depth - 1);
        }
}

uint64_t Octree_Node::get_voxel(const Vector3D &point, int lod) {
    if (!aabb.contains(point)) {return 0;}

    if (is_leaf() || lod == 0) {
        return vox_ID.value_or(0);
    }

    for (int i = 0; i < 8; ++i) {
        if (children[i]->aabb.contains(point)) {
            return children[i]->get_voxel(point, lod - 1);
        }
    }
    
    return 0;
}
