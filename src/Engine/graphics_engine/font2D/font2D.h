#pragma once

#include "../prerequisites.h"

#include <SpriteFont.h>
#include <exception>
#include "../../math/rect.h"
class App_Window;
class Font2D
{
public:
    Font2D(const wchar_t* file_path, Render_System* render_system);
    Rect get_bounds(const wchar_t* text);
    ~Font2D();

private:
    std::unique_ptr<DirectX::DX11::SpriteFont> font {nullptr};
    std::unique_ptr<DirectX::DX11::SpriteBatch> batch {nullptr};

    Render_System* system {nullptr};
    friend class App_Window;
};