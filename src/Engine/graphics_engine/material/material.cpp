#include "material.h"

#include "../graphics_engine.h"
#include <exception>

Material::Material(const wchar_t* vert_shader_path, const wchar_t* pix_shader_path) {
    void* shader_byte_code = nullptr;
    size_t shader_size = 0;
    
    Graphics_Engine::get_engine()->get_render_system()->compile_vertex_shader(vert_shader_path,"main",&shader_byte_code,&shader_size);
    vert_shader = Graphics_Engine::get_engine()->get_render_system()->create_vertex_shader(shader_byte_code,shader_size);
    Graphics_Engine::get_engine()->get_render_system()->release_compiled_shader();

    if(!vert_shader) {throw std::exception("Failed to load Vertex Shader in Material!");}

    Graphics_Engine::get_engine()->get_render_system()->compile_pixel_shader(pix_shader_path, "main", &shader_byte_code, &shader_size);
    pix_shader = Graphics_Engine::get_engine()->get_render_system()->create_pixel_shader(shader_byte_code,shader_size);
    Graphics_Engine::get_engine()->get_render_system()->release_compiled_shader();

    if(!pix_shader) {throw std::exception("Failed to load Pixel Shader in Material!");}
}

Material::Material(const material_sptr &material) {
    vert_shader = material->vert_shader;
    pix_shader = material->pix_shader;
}

Material::~Material() {

}

void Material::add_texture(const texture_sptr &texture) {
    textures.push_back(texture);
}

void Material::remove_texture(UINT index) {
    if(index >= this->textures.size()) {return;}
    textures.erase(textures.begin() + index);
}

void Material::set_buffer_data(void *data, UINT data_size) {
    if(!const_buffer) {
        const_buffer = Graphics_Engine::get_engine()->get_render_system()->create_constant_buffer(data, data_size);
    } else {
        const_buffer->update(Graphics_Engine::get_engine()->get_render_system()->get_device_context(),data);
    }
}

void Material::set_culling_mode(CULL_MODE mode) {
    culling_mode = mode;
}

CULL_MODE Material::get_culling_mode() {
    return culling_mode;
}
