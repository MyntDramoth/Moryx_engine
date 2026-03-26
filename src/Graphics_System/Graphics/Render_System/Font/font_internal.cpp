#include "font_internal.h"
#include "../render_system.h"

Font_Internal::Font_Internal(const wchar_t* full_path,const Render_System& render_system): m_renderer(render_system) {
   
    font = std::make_unique<DirectX::DX11::SpriteFont>(m_renderer.device.Get(),full_path);
    if(!font) {
       MORYX_ERROR("Failed to create Font!");
    }

    auto context = m_renderer.device_context;
    batch = std::make_unique<DirectX::DX11::SpriteBatch>(context->device_context.Get());
     if(!batch) {
        MORYX_ERROR("Failed to create Font!");
    }

}

Rect Font_Internal::get_bounds(const wchar_t *text)
{
    auto rc = font->MeasureDrawBounds(text,DirectX::XMFLOAT2(0.0f,0.0f));
    return Rect(rc.right - rc.left,rc.bottom - rc.top,rc.left,rc.top);
}

Font_Internal::~Font_Internal()
{

}

