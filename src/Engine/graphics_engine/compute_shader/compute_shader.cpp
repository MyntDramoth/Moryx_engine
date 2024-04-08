#include "compute_shader.h"

#include <exception>

#include "../render_system/render_system.h"

Compute_Shader::Compute_Shader(const void* shader_byte_code, size_t byte_code_size, Render_System* system) {
    HRESULT hres = render_system->device->CreateComputeShader(shader_byte_code,byte_code_size,nullptr,&compute_shader);
    if(FAILED(hres)) {
        throw std::exception("Failed to create Compute Shader!");
    }
}

Compute_Shader::~Compute_Shader() {
    compute_shader->Release();
}