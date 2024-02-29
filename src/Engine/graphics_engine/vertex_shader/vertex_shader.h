#pragma once

#include <d3d11.h>
#include "../device_context/device_context.h"

#include "../prerequisites.h"

class Vertex_Shader
{
public:
    Vertex_Shader(const void* shader_byte_code, size_t byte_code_size, Render_System* system);
    ~Vertex_Shader();

private:

    ID3D11VertexShader* vertex_shader;
    Render_System* render_system {nullptr};

    friend class Render_System;
    friend class Device_Context;
};