#pragma once
#include "../../../prerequisites.h"
#include "../../../Math/rect.h"
#include <SpriteFont.h>
#include <exception>
#include <wrl.h>
#include <d3d11.h>

class Font_Internal
{
public:
    Font_Internal(const wchar_t* full_path,Render_System* render_system);
    ~Font_Internal();
    Rect get_bounds(const wchar_t* text);

private:
    std::unique_ptr<DirectX::DX11::SpriteFont> font {nullptr};
    std::unique_ptr<DirectX::DX11::SpriteBatch> batch {nullptr};

    Render_System* render_system {nullptr};

    friend class Graphics_Engine;
};

