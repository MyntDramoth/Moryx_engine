#include "vertex_shader.h"


Vertex_Shader::Vertex_Shader()
{

}

Vertex_Shader::~Vertex_Shader()
{

}

bool Vertex_Shader::release()
{
    vertex_shader->Release();
    delete this;
    return true;
}

bool Vertex_Shader::init(const void* shader_byte_code, size_t byte_code_size)
{
   
    HRESULT hres = Graphics_Engine::get_engine()->device->CreateVertexShader(shader_byte_code,byte_code_size,nullptr,&vertex_shader);
    if(FAILED(hres)) {
        return false;
    }
    return true;
}
