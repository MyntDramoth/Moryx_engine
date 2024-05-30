#pragma once

#include "../../../prerequisites.h"
#include "../../../Math/rect.h"
#include <wrl.h>
#include <d3d11.h>

class Texture_Internal
{
public:
    enum Texture_Type {
        NORMAL = 0,
        RENDER_TARGET,
        DEPTH_STENCIL
    };

    Texture_Internal(const wchar_t* full_path,Render_System* render_system);
    Texture_Internal(const Rect& size, Texture_Internal::Texture_Type tex_type, Render_System* render_system);
    ~Texture_Internal();

    Rect get_size();
    Texture_Internal::Texture_Type get_type();

private:

    Microsoft::WRL::ComPtr<ID3D11Resource> texture = nullptr;
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> shader_view = nullptr;
    Microsoft::WRL::ComPtr<ID3D11RenderTargetView> target_view = nullptr;
    Microsoft::WRL::ComPtr<ID3D11DepthStencilView> stencil_view = nullptr;
    Microsoft::WRL::ComPtr<ID3D11SamplerState> sampler_state = nullptr;

    Texture_Internal::Texture_Type type = Texture_Internal::Texture_Type::NORMAL;
    Rect size;

    Render_System* render_system {nullptr};
    
    friend class Device_Context;
};