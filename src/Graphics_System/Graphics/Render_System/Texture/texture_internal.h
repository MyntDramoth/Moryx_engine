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
        DEPTH_STENCIL,
        TEXTURE_ARRAY
    };

    Texture_Internal(const wchar_t* full_path,const Render_System& render_system);
    Texture_Internal(const Rect& size, Texture_Internal::Texture_Type tex_type, const Render_System& render_system, uint32_t array_size = 1);
    ~Texture_Internal();

    Rect get_size();
    Texture_Internal::Texture_Type get_type();
    void populate_texture_array(std::vector<const wchar_t*> full_paths);

private:

    Microsoft::WRL::ComPtr<ID3D11Resource> texture = nullptr;
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> shader_view = nullptr;
    Microsoft::WRL::ComPtr<ID3D11RenderTargetView> target_view = nullptr;
    Microsoft::WRL::ComPtr<ID3D11DepthStencilView> stencil_view = nullptr;
    Microsoft::WRL::ComPtr<ID3D11SamplerState> sampler_state = nullptr;

    Texture_Internal::Texture_Type m_type = Texture_Internal::Texture_Type::NORMAL;
    Rect m_size;

    const Render_System& m_renderer;
    
    friend class Device_Context;
    friend class Render_System;
};