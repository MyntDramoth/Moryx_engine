#include "pixel_shader.h"

#include <exception>

#include "../render_system/render_system.h"

Pixel_Shader::Pixel_Shader(const void* shader_byte_code, size_t byte_code_size, Render_System* system) : render_system(system)
{
    HRESULT hres = render_system->device->CreatePixelShader(shader_byte_code,byte_code_size,nullptr,&pixel_shader);
    if(FAILED(hres)) {
        throw std::exception("failed to create Pixel Shader!");
    }
}

Pixel_Shader::~Pixel_Shader()
{
     pixel_shader->Release();
}