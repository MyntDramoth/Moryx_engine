#include "font_internal.h"
#include "../render_system.h"

Font_Internal::Font_Internal(const wchar_t* full_path,Render_System* render_system): render_system(render_system) {
   
    font = std::make_unique<DirectX::DX11::SpriteFont>(render_system->device.Get(),full_path);
    if(!font) {
       MORYX_ERROR("Failed to create Font!");
    }

    auto context = render_system->device_context;
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

