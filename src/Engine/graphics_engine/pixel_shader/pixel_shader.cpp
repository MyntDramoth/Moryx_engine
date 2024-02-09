#include "pixel_shader.h"

Pixel_Shader::Pixel_Shader()
{

}

Pixel_Shader::~Pixel_Shader()
{

}

bool Pixel_Shader::release()
{
    pixel_shader->Release();
    delete this;
    return true;
}

bool Pixel_Shader::init(const void* shader_byte_code, size_t byte_code_size)
{
   
    HRESULT hres = Graphics_Engine::get_engine()->device->CreatePixelShader(shader_byte_code,byte_code_size,nullptr,&pixel_shader);
    if(FAILED(hres)) {
        return false;
    }
    return true;
}
