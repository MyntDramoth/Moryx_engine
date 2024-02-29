#include "vertex_shader.h"

#include <exception>

#include "../render_system.h"

Vertex_Shader::Vertex_Shader(const void* shader_byte_code, size_t byte_code_size, Render_System *system) : render_system(system) {
     HRESULT hres = render_system->device->CreateVertexShader(shader_byte_code,byte_code_size,nullptr,&vertex_shader);
    if(FAILED(hres)) {
        throw std::exception("Failed to create Vertex Shader!");
    }
}

Vertex_Shader::~Vertex_Shader() {
     vertex_shader->Release();
}
