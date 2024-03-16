#include "swapchain.h"

#include <exception>

#include "../render_system/render_system.h"

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
    desc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
    desc.Windowed = TRUE;

    HRESULT hres = render_system->dxgi_factory->CreateSwapChain(d3_device,&desc,&swapchain);
    if(FAILED(hres)) {
        throw std::exception("Failed to create Swap Chain!");
    }
    reload_buffers(width,height);
    
}

Swapchain::~Swapchain()
{
    swapchain->Release();
    target_view->Release();
    stencil_view->Release();
}

void Swapchain::resize_swapchain(UINT width, UINT height) {
    if(target_view) {target_view->Release();}
    if(stencil_view) {stencil_view->Release();}

    swapchain->ResizeBuffers(1,width,height,DXGI_FORMAT_R8G8B8A8_UNORM,0);
    reload_buffers(width,height);
}

void Swapchain::set_fullsreen_state(bool is_fullscreen, UINT width, UINT height) {
    resize_swapchain(width,height);
    swapchain->SetFullscreenState(is_fullscreen,nullptr);
   
}

bool Swapchain::present(bool vsync)
{
    swapchain->Present(vsync,NULL);

    return true;
}

void Swapchain::reload_buffers(UINT width, UINT height) {
    ID3D11Texture2D* back_buffer = NULL;
    ID3D11Device* d3_device =  render_system->device;
    HRESULT hres = swapchain->GetBuffer(0,__uuidof(ID3D11Texture2D),(void**)&back_buffer);
    if(FAILED(hres)) {
        throw std::exception("Failed to get Swap Chain buffer!");
    }

    hres = d3_device->CreateRenderTargetView(back_buffer,NULL,&target_view);
    back_buffer->Release();

    if(FAILED(hres)) {
        throw std::exception("Failed to create Render Target View!");
    }

    D3D11_TEXTURE2D_DESC tex_desc = {};
    tex_desc.Width = width;
    tex_desc.Height = height;
    tex_desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    tex_desc.Usage = D3D11_USAGE_DEFAULT;
    tex_desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    tex_desc.MipLevels = 1;
    tex_desc.SampleDesc.Count = 1;
    tex_desc.SampleDesc.Quality = 0;
    tex_desc.MiscFlags = 0;
    tex_desc.ArraySize = 1;
    tex_desc.CPUAccessFlags = 0;

    hres = d3_device->CreateTexture2D(&tex_desc,nullptr,&back_buffer);
    if(FAILED(hres)) {
        throw std::exception("Failed to create Depth Buffer!");
    }

   
    hres = d3_device->CreateDepthStencilView(back_buffer,NULL,&stencil_view);
    back_buffer->Release();
}
