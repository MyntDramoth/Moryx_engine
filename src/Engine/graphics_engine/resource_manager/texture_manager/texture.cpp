#include "texture.h"

#include <DirectXTex.h>

#include "../../graphics_engine.h"

Texture::Texture(const wchar_t* full_path):Resource(full_path) {
    
    DirectX::ScratchImage image_data;

    HRESULT res = DirectX::LoadFromWICFile(full_path,DirectX::WIC_FLAGS_NONE,nullptr,image_data);

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

        Graphics_Engine::get_engine()->get_render_system()->device->CreateShaderResourceView(texture,&desc,&shader_view);
    } else {throw std::exception("failed to load image!");}
}

Texture::~Texture() {
    shader_view->Release();
    texture->Release();
}