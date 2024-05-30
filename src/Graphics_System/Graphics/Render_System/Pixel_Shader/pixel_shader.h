#pragma once

#include <d3d11.h>
#include "../Device_Context/device_context.h"

#include "../../../prerequisites.h"

class Pixel_Shader
{
public:
    Pixel_Shader(const wchar_t* full_path, const char* entry_point, Render_System* system);
    ~Pixel_Shader();

private:

    Microsoft::WRL::ComPtr<ID3D11PixelShader> pixel_shader;
    Render_System* render_system {nullptr};

    friend class Render_System;
    friend class Device_Context;
};
