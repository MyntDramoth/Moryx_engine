#pragma once

#include "../graphics_engine.h"
#include "../device_context/device_context.h"

class Graphics_Engine;
class Device_Context;

class Pixel_Shader
{
public:
    Pixel_Shader();
    ~Pixel_Shader();

   
    bool release();

private:
    bool init(const void* shader_byte_code, size_t byte_code_size);

    ID3D11PixelShader* pixel_shader;

    friend class Graphics_Engine;
    friend class Device_Context;
};
