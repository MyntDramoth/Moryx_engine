#pragma once

#include <d3d11.h>
#include "../Device_Context/device_context.h"

#include "../../../prerequisites.h"

class Swapchain {
public:
    Swapchain(const HWND &hwnd,const uint32_t &width,const uint32_t &height,  const Render_System& system);
    ~Swapchain();
    
    void resize_swapchain(const uint32_t &width,const uint32_t &height);
    void set_fullsreen_state(const bool &is_fullscreen, const uint32_t &width, const uint32_t &height);
    bool present(const bool &vsync);

private:

    void reload_buffers(const uint32_t &width, const uint32_t &height);

    Microsoft::WRL::ComPtr<IDXGISwapChain> swapchain = nullptr;
    Microsoft::WRL::ComPtr<ID3D11RenderTargetView> target_view = nullptr;
    Microsoft::WRL::ComPtr<ID3D11DepthStencilView> stencil_view = nullptr;
    const Render_System& m_renderer;

    friend class Device_Context;
};