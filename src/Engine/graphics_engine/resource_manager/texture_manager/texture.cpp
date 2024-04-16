#include "texture.h"

#include <DirectXTex.h>

#include "../../graphics_engine.h"
#include <filesystem>
#include <exception>
#include <iostream>


Texture::Texture(const wchar_t* full_path):Resource(full_path) {
    
   if(!std::filesystem::exists(full_path)) {
        std::cout<<"File path is wrong or file does not exist!" << " || File name: " << std::filesystem::path(full_path).filename()<<"\n";
        throw std::exception("File path is wrong or file does not exist!");    
    }
    
    DirectX::ScratchImage image_data;

    HRESULT res = DirectX::LoadFromWICFile(full_path,DirectX::WIC_FLAGS_IGNORE_SRGB,nullptr,image_data);

    if(SUCCEEDED(res)) {
        res = DirectX::CreateTexture(Graphics_Engine::get_engine()->get_render_system()->device,
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
        sampler_desc.MaxLOD = (UINT)image_data.GetMetadata().mipLevels;

        res = Graphics_Engine::get_engine()->get_render_system()->device->CreateSamplerState(&sampler_desc,&sampler_state);

        if(FAILED(res)) { throw std::exception("failed to create sampler state!");}

        res = Graphics_Engine::get_engine()->get_render_system()->device->CreateShaderResourceView(texture,&desc,&shader_view);

        if(FAILED(res)) { throw std::exception("failed to resource view!");}
    } else {throw std::exception("failed to load image!");}
}

Texture::Texture(const Rect &size, Texture::Texture_Type tex_type): Resource(L"") {
    
    D3D11_TEXTURE2D_DESC tex_desc = {};
    tex_desc.Width = size.width;
    tex_desc.Height = size.height;

    if(tex_type == NORMAL) {
        tex_desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        tex_desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
    }
    if(tex_type == RENDER_TARGET) {
        tex_desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        tex_desc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
    }
    if(tex_type == DEPTH_STENCIL) {
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

    auto hres = Graphics_Engine::get_engine()->get_render_system()->device->CreateTexture2D(&tex_desc,nullptr,(ID3D11Texture2D**)&texture);
    if(FAILED(hres)) {
        throw std::exception("Failed to create Texture!");
    }

   
    if(tex_type == NORMAL || tex_type == RENDER_TARGET) {
        hres = Graphics_Engine::get_engine()->get_render_system()->device->CreateShaderResourceView(texture,NULL,&shader_view);
    }
    if(tex_type == RENDER_TARGET) {
        hres = Graphics_Engine::get_engine()->get_render_system()->device->CreateRenderTargetView(texture,NULL,&target_view);
    }
    if(tex_type == DEPTH_STENCIL) {
        hres = Graphics_Engine::get_engine()->get_render_system()->device->CreateDepthStencilView(texture,NULL,&stencil_view);
    }

    if(FAILED(hres)) {
        throw std::exception("Failed to create Texture!");
    }
}

Texture::~Texture() {
    if(sampler_state) {sampler_state->Release();}
    if(target_view) {target_view->Release();}
    if(stencil_view) {stencil_view->Release();}
    if(shader_view) {shader_view->Release();}
    if(texture) {texture->Release();}
}

Rect Texture::get_size()
{
    return size;
}

Texture::Texture_Type Texture::get_type()
{
    return type;
}
