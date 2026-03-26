
#include <DirectXTex.h>
#include <filesystem>
#include <exception>
#include <iostream>

#include "../render_system.h"
#include "texture_internal.h"

Texture_Internal::Texture_Internal(const wchar_t* full_path, const Render_System& render_system):m_renderer(render_system) {
     
    DirectX::ScratchImage image_data;

    HRESULT res = DirectX::LoadFromWICFile(full_path,DirectX::WIC_FLAGS_IGNORE_SRGB,nullptr,image_data);

    if (FAILED(res))
    {
        MORYX_ERROR("Failed to load texture: " << std::filesystem::path(full_path).filename());
    }

    if(SUCCEEDED(res)) {
        res = DirectX::CreateTexture(m_renderer.device.Get(),
        image_data.GetImages(),
        image_data.GetImageCount(),
        image_data.GetMetadata(),
        &texture);

        D3D11_SHADER_RESOURCE_VIEW_DESC desc = {};
        desc.Format = image_data.GetMetadata().format;
        desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
        desc.Texture2D.MipLevels = (UINT)image_data.GetMetadata().mipLevels;
        desc.Texture2D.MostDetailedMip = 0;

        //MORYX_INFO("Format: " << desc.Format);
        D3D11_SAMPLER_DESC sampler_desc = {};
        sampler_desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
        sampler_desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
        sampler_desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
        sampler_desc.Filter = D3D11_FILTER_ANISOTROPIC;
        sampler_desc.MinLOD = 0;
        sampler_desc.MaxLOD = (float)image_data.GetMetadata().mipLevels;
       

        res = m_renderer.device->CreateSamplerState(&sampler_desc,&sampler_state);

        if(FAILED(res)) { MORYX_ERROR("failed to create sampler state!");}

        res = m_renderer.device->CreateShaderResourceView(texture.Get(),&desc,&shader_view);

        if(FAILED(res)) { MORYX_ERROR("failed to resource view!");}
    } else {MORYX_ERROR("failed to load image!");}
}

Texture_Internal::Texture_Internal(const Rect &size, Texture_Internal::Texture_Type tex_type, const Render_System& render_system, uint32_t array_size):m_renderer(render_system) {
   
    D3D11_TEXTURE2D_DESC tex_desc = {};
    tex_desc.Width = size.width;
    tex_desc.Height = size.height;
    m_size = size;
    if(tex_type == NORMAL) {
        tex_desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        tex_desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
        tex_desc.ArraySize = 1;
    }
    else if(tex_type == RENDER_TARGET) {
        tex_desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        tex_desc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
        tex_desc.ArraySize = 1;
    }
    else if(tex_type == DEPTH_STENCIL) {
        tex_desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
        tex_desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
        tex_desc.ArraySize = 1;
    }
    else if(tex_type == TEXTURE_ARRAY) {
        tex_desc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
        tex_desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
        tex_desc.ArraySize = array_size;
        if(array_size < 1) {MORYX_ERROR("Array size needs to be at least 1!");}
    }

    tex_desc.Usage = D3D11_USAGE_DEFAULT;
    tex_desc.MipLevels = 1;
    tex_desc.SampleDesc.Count = 1;
    tex_desc.SampleDesc.Quality = 0;
    tex_desc.MiscFlags = 0;
    tex_desc.CPUAccessFlags = 0;

    HRESULT hres = m_renderer.device->CreateTexture2D(&tex_desc,nullptr,(ID3D11Texture2D**)texture.GetAddressOf());
   
    if(FAILED(hres)) {
        MORYX_ERROR("Failed to create Texture!");
    }

    if(tex_type == NORMAL || tex_type == RENDER_TARGET) {
        hres = m_renderer.device->CreateShaderResourceView(texture.Get(),NULL,&shader_view);
        if(FAILED(hres)) {
        MORYX_ERROR("Failed to create Resource View!");
        }
    }
    if(tex_type == RENDER_TARGET) {
        hres = m_renderer.device->CreateRenderTargetView(texture.Get(),NULL,&target_view);
        if(FAILED(hres)) {
        MORYX_ERROR("Failed to create Target View!");
        }
    }
    else if(tex_type == DEPTH_STENCIL) {
        hres = m_renderer.device->CreateDepthStencilView(texture.Get(),NULL,&stencil_view);
        if(FAILED(hres)) {
        MORYX_ERROR("Failed to create Depth View!");
        }
    }
    else if (tex_type == TEXTURE_ARRAY) {

        D3D11_SHADER_RESOURCE_VIEW_DESC srv_desc = {};
        srv_desc.Format = tex_desc.Format;
        srv_desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2DARRAY;
        srv_desc.Texture2DArray.MostDetailedMip = 0;
        srv_desc.Texture2DArray.MipLevels = 1;
        srv_desc.Texture2DArray.FirstArraySlice = 0;
        srv_desc.Texture2DArray.ArraySize = array_size;

        D3D11_SAMPLER_DESC sampler_desc = {};
        sampler_desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
        sampler_desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
        sampler_desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
        sampler_desc.Filter = D3D11_FILTER_ANISOTROPIC;
        sampler_desc.MinLOD = 0;
        sampler_desc.MaxLOD = D3D11_FLOAT32_MAX;

        m_renderer.device->CreateSamplerState(&sampler_desc, &sampler_state);

        hres = m_renderer.device->CreateShaderResourceView(texture.Get(),&srv_desc,&shader_view);
        if(FAILED(hres)) {
        MORYX_ERROR("Failed to create Resource View!");
        }
    }
   
}

Texture_Internal::~Texture_Internal()
{
}

Rect Texture_Internal::get_size()
{
    return m_size;
}

Texture_Internal::Texture_Type Texture_Internal::get_type()
{
    return m_type;
}



void Texture_Internal::populate_texture_array(std::vector<const wchar_t*> full_paths) {

    DXGI_FORMAT base_format = DXGI_FORMAT_R8G8B8A8_UNORM;

    for(int32_t i = 0; i < full_paths.size();i++) {
      
        DirectX::ScratchImage image_data;
        HRESULT res = DirectX::LoadFromWICFile(full_paths[i],DirectX::WIC_FLAGS_IGNORE_SRGB,nullptr,image_data);

        if (FAILED(res))
        {
            MORYX_ERROR("Failed to load texture: " << std::filesystem::path(full_paths[i]).filename());
        }

        const DirectX::Image* img = image_data.GetImage(0, 0, 0);
        auto meta = image_data.GetMetadata();
        if(i == 0) {base_format = meta.format;}
        
        if ( m_size.width != meta.width || m_size.height != meta.height || base_format != meta.format) {
             MORYX_ERROR("All textures must have identical height, width, and format!");
        }
        
        UINT subresource = D3D11CalcSubresource(0, i, 1);

        m_renderer.context->UpdateSubresource(
            texture.Get(),
            subresource,
            nullptr,
            img->pixels,
            img->rowPitch,
            0
        );
    }
}
