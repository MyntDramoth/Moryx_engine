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

flecs::entity entity_handler::create_light(const char *name)
{
    auto e = world.entity(name);
    e.is_alive();
    e.add<Transform>();
    e.add<Light>();
    entities.insert({(size_t)name,e});
    lights.insert({(size_t)name,e});
    return e;
}

flecs::entity entity_handler::create_text(const char *name)
{
   auto e = world.entity(name);
    e.is_alive();
    e.add<Transform>();
    e.add<Text>();
    entities.insert({(size_t)name,e});
    text.insert({(size_t)name,e});
    return e;
}

flecs::entity entity_handler::create_UI_image(const char *name)
{
    auto e = world.entity(name);
    e.is_alive();
    e.add<Transform>();
    e.add<Image>();
    entities.insert({(size_t)name,e});
    images.insert({(size_t)name,e});
    return e;
}

flecs::entity entity_handler::create_animated_sprite(const char *name)
{
    auto e = world.entity(name);
    e.is_alive();
    e.add<Transform>();
    e.add<Animation_2D>();
    entities.insert({(size_t)name,e});
    sprites.insert({(size_t)name,e});
    return e;
}

void entity_handler::register_mesh(flecs::entity entity) {
    entity.add<M_Mesh>();
    const char *name = entity.name();
    meshes.insert({(size_t)name,entity});
}

void entity_handler::register_instance_mesh(flecs::entity entity) {
    entity.add<M_Mesh>();
    const char *name = entity.name();
    instance_meshes.insert({(size_t)name,entity});
}
