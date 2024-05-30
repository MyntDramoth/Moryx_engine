#pragma once

#include <d3d11.h>
#include "../Device_Context/device_context.h"

#include "../../../prerequisites.h"

class Swapchain {
public:
    Swapchain(HWND hwnd,UINT width, UINT height, Render_System* system);
    ~Swapchain();
    
    void resize_swapchain(UINT width, UINT height);
    void set_fullsreen_state(bool is_fullscreen, UINT width, UINT height);
    bool present(bool vsync);

private:

    void reload_buffers(UINT width, UINT height);

     Microsoft::WRL::ComPtr<IDXGISwapChain> swapchain = nullptr;
     Microsoft::WRL::ComPtr<ID3D11RenderTargetView> target_view = nullptr;
     Microsoft::WRL::ComPtr<ID3D11DepthStencilView> stencil_view = nullptr;
    Render_System* render_system {nullptr};

    friend class Device_Context;
};