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

Texture::~Texture() {
    sampler_state->Release();
    shader_view->Release();
    texture->Release();
}