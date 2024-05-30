#pragma once
#include <d3d11.h>
#include "../Device_Context/device_context.h"

#include "../../../prerequisites.h"

class Compute_Shader
{
public:
    Compute_Shader(const wchar_t* full_path, const char* entry_point, Render_System* system);
    ~Compute_Shader();

private:
    Microsoft::WRL::ComPtr<ID3D11ComputeShader> compute_shader;
    Render_System* render_system {nullptr};

    friend class Render_System;
    friend class Device_Context;

};