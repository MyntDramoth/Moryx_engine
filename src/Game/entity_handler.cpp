#include "entity_handler.h"
#include <stdio.h>
#include <iostream>

entity_handler::entity_handler()
{
    
}

entity_handler::~entity_handler()
{

}

void entity_handler::purge_entities(float time) {
   for(auto&& [size_t,entity] : entities) {
        if(!entity.is_alive()) {entity.destruct();}
   }
}

flecs::entity entity_handler::create_entity(const char *name)
{
    auto e = world.entity(name);
    e.is_alive();

    entities.insert({(size_t)name,e});
    return e;
}

flecs::entity entity_handler::create_camera(const char *name)
{
    auto e = world.entity(name);
    e.is_alive();
    e.add<Transform>();
    e.add<Camera>();
    entities.insert({(size_t)name,e});
    cameras.insert({(size_t)name,e});
    return e;
}

void entity_handler::register_mesh(flecs::entity entity) {
    entity.add<M_Mesh>();
    const char *name = entity.name();
    meshes.insert({(size_t)name,entity});
}
