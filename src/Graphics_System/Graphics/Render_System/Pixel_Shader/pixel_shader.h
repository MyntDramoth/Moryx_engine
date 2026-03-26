#pragma once

#include <d3d11.h>
#include "../Device_Context/device_context.h"

#include "../../../prerequisites.h"

class Pixel_Shader
{
public:
    Pixel_Shader(const wchar_t* full_path, const char* entry_point, const Render_System& system);
    ~Pixel_Shader();

private:

    Microsoft::WRL::ComPtr<ID3D11PixelShader> pixel_shader;
    const Render_System& m_renderer;

    friend class Render_System;
    friend class Device_Context;
};
