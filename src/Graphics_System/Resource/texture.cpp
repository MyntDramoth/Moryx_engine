#include "texture.h"
#include "resource_manager.h"

Texture::Texture(const wchar_t *full_path, Resource_Manager *manager):Resource(full_path,manager) {
    
    texture = manager->get_game()->get_graphics_engine()->get_render_system()->create_texture(full_path);
}
