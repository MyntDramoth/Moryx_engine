#include "swapchain.h"

#include <exception>

#include "../render_system.h"

Swapchain::Swapchain(HWND hwnd,UINT width, UINT height, Render_System* system) : render_system(system)
{
    ID3D11Device* d3_device =  render_system->device;

    DXGI_SWAP_CHAIN_DESC desc;
    ZeroMemory(&desc, sizeof(desc));
    desc.BufferCount = 1;
    desc.BufferDesc.Width = width;
    desc.BufferDesc.Height = height;
    desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    desc.BufferDesc.RefreshRate.Numerator = 60;
    desc.BufferDesc.RefreshRate.Denominator = 1;
    desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    desc.OutputWindow = hwnd;
    desc.SampleDesc.Count = 1;
    desc.SampleDesc.Quality = 0;
    desc.Windowed = TRUE;

    HRESULT hres = render_system->dxgi_factory->CreateSwapChain(d3_device,&desc,&swapchain);
    if(FAILED(hres)) {
        throw std::exception("Failed to create Swap Chain!");
    }

    ID3D11Texture2D* back_buffer = NULL;
    hres = swapchain->GetBuffer(0,__uuidof(ID3D11Texture2D),(void**)&back_buffer);
    if(FAILED(hres)) {
        throw std::exception("Failed to get Swap Chain buffer!");
    }

    hres = d3_device->CreateRenderTargetView(back_buffer,NULL,&target_view);
    back_buffer->Release();

    if(FAILED(hres)) {
        throw std::exception("Failed to create Render Target View!");
    }

   
}

Swapchain::~Swapchain()
{
    swapchain->Release();
    target_view->Release();
}



bool Swapchain::present(bool vsync)
{
    swapchain->Present(vsync,NULL);

    return true;
}
