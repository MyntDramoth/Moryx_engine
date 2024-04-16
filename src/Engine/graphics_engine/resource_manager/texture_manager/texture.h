#pragma once

#include "../resource.h"
#include "../../prerequisites.h"
#include "../../../math/rect.h"

#include <d3d11.h>

class Texture : public Resource
{
public:
    enum Texture_Type {
        NORMAL = 0,
        RENDER_TARGET,
        DEPTH_STENCIL
    };

    Texture(const wchar_t* full_path);
    Texture(const Rect& size, Texture::Texture_Type tex_type);
    ~Texture();

    Rect get_size();
    Texture::Texture_Type get_type();

private:

    ID3D11Resource* texture = nullptr;
    ID3D11ShaderResourceView* shader_view = nullptr;
    ID3D11RenderTargetView* target_view = nullptr;
     ID3D11DepthStencilView* stencil_view = nullptr;
    ID3D11SamplerState* sampler_state = nullptr;

    Texture::Texture_Type type = Texture::Texture_Type::NORMAL;
    Rect size;

    friend class Device_Context;
};