#include "swapchain.h"

Swapchain::Swapchain()
{
}

Swapchain::~Swapchain()
{
}

bool Swapchain::init(HWND hwnd,UINT width, UINT height)
{

    ID3D11Device* d3_device =  Graphics_Engine::get_engine()->device;

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

    HRESULT hres = Graphics_Engine::get_engine()->dxgi_factory->CreateSwapChain(d3_device,&desc,&swapchain);
    if(FAILED(hres)) {
        return false;
    }

    ID3D11Texture2D* back_buffer = NULL;
    hres = swapchain->GetBuffer(0,__uuidof(ID3D11Texture2D),(void**)&back_buffer);
    if(FAILED(hres)) {
        return false;
    }

    hres = d3_device->CreateRenderTargetView(back_buffer,NULL,&target_view);
    back_buffer->Release();

    if(FAILED(hres)) {
        return false;
    }

    return true;
}

bool Swapchain::present(bool vsync)
{
    swapchain->Present(vsync,NULL);

    return true;
}

bool Swapchain::release()
{
    swapchain->Release();
    target_view->Release();
    delete this;
    return true;
}
