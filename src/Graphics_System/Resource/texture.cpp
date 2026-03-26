#include "texture.h"
#include "resource_manager.h"

Texture::Texture(const wchar_t *full_path, Resource_Manager *manager):Resource(full_path,manager) {
    
    texture = manager->get_game()->get_graphics_engine()->get_render_system()->create_texture(full_path);
}

Texture::Texture(const Rect& size, Texture_Internal::Texture_Type tex_type,Resource_Manager *manager, uint32_t array_size):Resource(L"",manager) {
    texture = manager->get_game()->get_graphics_engine()->get_render_system()->create_texture(size,tex_type,array_size);
}