#pragma once

#include <d3d11.h>
#include "../device_context/device_context.h"

#include "../prerequisites.h"

class Pixel_Shader
{
public:
    Pixel_Shader(const void* shader_byte_code, size_t byte_code_size, Render_System* system);
    ~Pixel_Shader();

private:

    ID3D11PixelShader* pixel_shader;
    Render_System* render_system {nullptr};

    friend class Render_System;
    friend class Device_Context;
};
