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

void entity_handler::register_mesh(flecs::entity entity) {
    entity.add<M_Mesh>();
    const char *name = entity.name();
    meshes.insert({(size_t)name,entity});
}

void entity_handler::bind_transform_to_mesh(flecs::entity entity) {
    auto transform = entity.get_ref<Transform>();
    transform->world_matrix.set_identity();
    transform->world_matrix.set_scale(transform->scale);
    
    transform->world_matrix.set_rotation_x(transform->rotation.x);
    transform->world_matrix.set_rotation_y(transform->rotation.y);
    transform->world_matrix.set_rotation_z(transform->rotation.z);

    
    transform->world_matrix.set_translation(transform->position);
}
