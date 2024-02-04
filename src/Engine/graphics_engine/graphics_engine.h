#pragma once

#include <d3d11.h>
#include "swapchain/swapchain.h"

class Swapchain;

class Graphics_Engine {
public:
    Graphics_Engine();
    ~Graphics_Engine();
    bool init();
    bool release();

    static Graphics_Engine* get_engine();

    Swapchain * create_swap_chain();
    
private:
    ID3D11Device* device;
    D3D_FEATURE_LEVEL m_feature_level;
    // or Immediate Device Contact Spider
    ID3D11DeviceContext* m_device_context;

    IDXGIDevice* dxgi_device;
    IDXGIAdapter* dxgi_adapter;
    IDXGIFactory* dxgi_factory;

    friend class Swapchain;
};