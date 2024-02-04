#include "graphics_engine.h"


Graphics_Engine::Graphics_Engine()
{
}

Graphics_Engine::~Graphics_Engine()
{
}

bool Graphics_Engine::init()
{
    D3D_DRIVER_TYPE driver_types[] = {
        D3D_DRIVER_TYPE_HARDWARE,
        D3D_DRIVER_TYPE_WARP,
        D3D_DRIVER_TYPE_REFERENCE
    };

     UINT num_drivers = ARRAYSIZE(driver_types);

    D3D_FEATURE_LEVEL feature_levels[] = {
        D3D_FEATURE_LEVEL_11_0
    };

     UINT num_feat_levels = ARRAYSIZE(feature_levels);
    HRESULT hres = 0;
    for (UINT driver_index = 0; driver_index < num_drivers;) {


        hres = D3D11CreateDevice(NULL,driver_types[driver_index],NULL,NULL,feature_levels,num_feat_levels,D3D11_SDK_VERSION,
        &device,&m_feature_level,&m_device_context
        );
        if(SUCCEEDED(hres)) {
            break;
        }

        ++driver_index;
    }

    if(FAILED(hres)) {return false;}

    device->QueryInterface(__uuidof(IDXGIDevice),(void**)&dxgi_device);
    dxgi_device->GetParent(__uuidof(IDXGIAdapter),(void**)&dxgi_adapter);
    dxgi_adapter->GetParent(__uuidof(IDXGIFactory),(void**)&dxgi_factory);



    return true;
}

bool Graphics_Engine::release()
{
    dxgi_device->Release();
    dxgi_adapter->Release();
    dxgi_factory->Release();

    m_device_context->Release();
    device->Release();
    return true;
}

Graphics_Engine* Graphics_Engine::get_engine()
{
    static Graphics_Engine engine;
    return &engine;
}

Swapchain * Graphics_Engine::create_swap_chain()
{
    return new Swapchain();
}
