#include "material.h"

#include <exception>
#include <filesystem>
#include <iostream>
#include "../Graphics/Render_System/Constant_Buffer/constant_buffer.h"
#include "../Graphics/Render_System/Pixel_Shader/pixel_shader.h"
#include "../Graphics/Render_System/Vertex_Shader/vertex_shader.h"
#include "../Graphics/Render_System/render_system.h"
#include "../../Game/game.h"

Material::Material(const wchar_t* shader_path, Resource_Manager* manager):Resource(shader_path,manager) {

    auto render_sys = manager->get_game()->get_graphics_engine()->get_render_system();
    
   
    vert_shader = render_sys->create_vertex_shader(shader_path,"vs_main");
    if(!vert_shader) {MORYX_ERROR("Failed to create material");}
    pix_shader = render_sys->create_pixel_shader(shader_path,"ps_main");
    if(!pix_shader) {MORYX_ERROR("Failed to create material");}

  
}

Material::Material(const material_sptr &material, Resource_Manager* manager):Resource(L"",manager) {
    vert_shader = material->vert_shader;
    pix_shader = material->pix_shader;
}

Material::~Material() {

}

void Material::add_texture(const texture_sptr &texture) {
    textures.push_back(texture->texture);
}

void Material::remove_texture(UINT index) {
    if(index >= this->textures.size()) {return;}
    textures.erase(textures.begin() + index);
}

void Material::set_buffer_data(void *data, UINT data_size) {
    
    auto render_sys = manager->get_game()->get_graphics_engine()->get_render_system();
    
    if(!const_buffer) {
        const_buffer = render_sys->create_constant_buffer(data, data_size);
       
    } else {
        const_buffer->update(render_sys->get_device_context(),data);
    }
}

void Material::set_culling_mode(CULL_MODE mode) {
    culling_mode = mode;
}

CULL_MODE Material::get_culling_mode() {
    return culling_mode;
}
