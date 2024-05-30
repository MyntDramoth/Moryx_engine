
#include <DirectXTex.h>
#include <filesystem>
#include <exception>
#include <iostream>

#include "../render_system.h"

Texture_Internal::Texture_Internal(const wchar_t* full_path, Render_System* render_system):render_system(render_system) {
    
   if(!std::filesystem::exists(full_path)) {
        MORYX_ERROR("File path is wrong or file does not exist!" << " || File name: " << std::filesystem::path(full_path).filename()); 
    }
    
    DirectX::ScratchImage image_data;

    HRESULT res = DirectX::LoadFromWICFile(full_path,DirectX::WIC_FLAGS_IGNORE_SRGB,nullptr,image_data);

    if(SUCCEEDED(res)) {
        res = DirectX::CreateTexture(render_system->device.Get(),
        image_data.GetImages(),
        image_data.GetImageCount(),
        image_data.GetMetadata(),
        &texture);

         D3D11_SHADER_RESOURCE_VIEW_DESC desc = {};
        desc.Format = image_data.GetMetadata().format;
        desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
        desc.Texture2D.MipLevels = (UINT)image_data.GetMetadata().mipLevels;
        desc.Texture2D.MostDetailedMip = 0;

        D3D11_SAMPLER_DESC sampler_desc = {};
        sampler_desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
        sampler_desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
        sampler_desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
        sampler_desc.Filter = D3D11_FILTER_ANISOTROPIC;
        sampler_desc.MinLOD = 0;
        sampler_desc.MaxLOD = (float)image_data.GetMetadata().mipLevels;

        res = render_system->device->CreateSamplerState(&sampler_desc,&sampler_state);

        if(FAILED(res)) { MORYX_ERROR("failed to create sampler state!");}

        res = render_system->device->CreateShaderResourceView(texture.Get(),&desc,&shader_view);

        if(FAILED(res)) { MORYX_ERROR("failed to resource view!");}
    } else {MORYX_ERROR("failed to load image!");}
}

Texture_Internal::Texture_Internal(const Rect &size, Texture_Internal::Texture_Type tex_type, Render_System* render_system):render_system(render_system) {
   
    D3D11_TEXTURE2D_DESC tex_desc = {};
    tex_desc.Width = size.width;
    tex_desc.Height = size.height;

    if(tex_type == NORMAL) {
        tex_desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        tex_desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
    }
    else if(tex_type == RENDER_TARGET) {
        tex_desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        tex_desc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
    }
    else if(tex_type == DEPTH_STENCIL) {
        tex_desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
        tex_desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    }

    tex_desc.Usage = D3D11_USAGE_DEFAULT;
    tex_desc.MipLevels = 1;
    tex_desc.SampleDesc.Count = 1;
    tex_desc.SampleDesc.Quality = 0;
    tex_desc.MiscFlags = 0;
    tex_desc.ArraySize = 1;
    tex_desc.CPUAccessFlags = 0;

    auto hres = render_system->device->CreateTexture2D(&tex_desc,nullptr,(ID3D11Texture2D**)texture.GetAddressOf());
    if(FAILED(hres)) {
        MORYX_ERROR("Failed to create Texture!");
    }

    if(tex_type == NORMAL || tex_type == RENDER_TARGET) {
        hres = render_system->device->CreateShaderResourceView(texture.Get(),NULL,&shader_view);
        if(FAILED(hres)) {
        MORYX_ERROR("Failed to create Resource View!");
        }
    }
    if(tex_type == RENDER_TARGET) {
        hres = render_system->device->CreateRenderTargetView(texture.Get(),NULL,&target_view);
        if(FAILED(hres)) {
        MORYX_ERROR("Failed to create Target View!");
        }
    }
    else if(tex_type == DEPTH_STENCIL) {
        hres = render_system->device->CreateDepthStencilView(texture.Get(),NULL,&stencil_view);
        if(FAILED(hres)) {
        MORYX_ERROR("Failed to create Depth View!");
        }
    }
   
}

Texture_Internal::~Texture_Internal() {
}

Rect Texture_Internal::get_size()
{
    return size;
}

Texture_Internal::Texture_Type Texture_Internal::get_type()
{
    return type;
}
