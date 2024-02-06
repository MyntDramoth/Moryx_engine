#pragma once

#include "../graphics_engine.h"
#include "../device_context/device_context.h"

class Device_Context;

class Swapchain {
public:
    Swapchain();
    ~Swapchain();
    bool init(HWND hwnd,UINT width, UINT height);
    bool present(bool vsync);
    bool release();
private:
    IDXGISwapChain* swapchain;
    ID3D11RenderTargetView* target_view;

    friend class Device_Context;
};