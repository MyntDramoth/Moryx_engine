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
    flecs::entity create_camera(const char* name);
    flecs::entity create_light(const char* name);
    flecs::entity create_text(const char* name);
    flecs::entity create_UI_image(const char* name);
    flecs::entity create_animated_sprite(const char* name);
    void register_mesh(flecs::entity entity);
    
    std::map<size_t,flecs::entity> get_meshes() {return meshes;}
    std::map<size_t,flecs::entity> get_cams() {return cameras;}
    std::map<size_t,flecs::entity> get_lights() {return lights;}
    std::map<size_t,flecs::entity> get_text() {return text;}
    std::map<size_t,flecs::entity> get_images() {return images;}
    std::map<size_t,flecs::entity> get_sprites() {return sprites;}

private:
    flecs::world world;
    std::map<size_t,flecs::entity> entities;
    std::map<size_t,flecs::entity> meshes;
    std::map<size_t,flecs::entity> cameras;
    std::map<size_t,flecs::entity> lights;
    std::map<size_t,flecs::entity> text;
    std::map<size_t,flecs::entity> images;
    std::map<size_t,flecs::entity> sprites;
};