#pragma once

#include <d3d11.h>
#include "../device_context/device_context.h"

#include "../../prerequisites.h"

class Swapchain {
public:
    Swapchain(HWND hwnd,UINT width, UINT height, Render_System* system);
    ~Swapchain();
    
    bool present(bool vsync);

private:
    IDXGISwapChain* swapchain;
    ID3D11RenderTargetView* target_view;
    Render_System* render_system = nullptr;

    friend class Device_Context;
};