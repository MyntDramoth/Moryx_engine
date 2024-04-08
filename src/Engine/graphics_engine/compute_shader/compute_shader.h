#pragma once
#include <d3d11.h>
#include "../device_context/device_context.h"

#include "../prerequisites.h"

class Compute_Shader
{
public:
    Compute_Shader(const void* shader_byte_code, size_t byte_code_size, Render_System* system);
    ~Compute_Shader();

private:
    ID3D11ComputeShader* compute_shader;
    Render_System* render_system {nullptr};

    friend class Render_System;
    friend class Device_Context;

};