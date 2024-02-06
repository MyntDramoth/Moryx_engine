#pragma once

#include <d3d11.h>
#include "../swapchain/swapchain.h"

class Swapchain;

class Device_Context
{
public:
    Device_Context(ID3D11DeviceContext* context);
    ~Device_Context();

    bool clear_render_target_color(Swapchain* swapchain,float red, float green, float blue, float alpha);

    bool release();

private:
    ID3D11DeviceContext* device_context;
    
};