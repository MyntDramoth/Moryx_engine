#pragma once

#include <flecs.h>
#include <map>
#include "components.h"

class entity_handler
{
public:
    entity_handler();
    ~entity_handler();

    void purge_entities(float time);
    flecs::entity create_entity(const char* name);
    void register_mesh(flecs::entity entity);
    void bind_transform_to_mesh(flecs::entity entity);
    std::map<size_t,flecs::entity> get_meshes() {return meshes;}

private:
    flecs::world world;
    std::map<size_t,flecs::entity> entities;
    std::map<size_t,flecs::entity> meshes;
};