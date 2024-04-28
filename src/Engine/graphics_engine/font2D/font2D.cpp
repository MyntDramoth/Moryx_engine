#include "font2D.h"
#include "../render_system/render_system.h"

Font2D::Font2D(const wchar_t* file_path, Render_System* render_system) {
   
    font = std::make_unique<DirectX::DX11::SpriteFont>(render_system->device,file_path);
    if(!font) {
        throw std::exception("Failed to create Font!");
    }

    auto context = render_system->device_context;
    batch = std::make_unique<DirectX::DX11::SpriteBatch>(context->get_context());
     if(!batch) {
        throw std::exception("Failed to create Font!");
    }

}

Rect Font2D::get_bounds(const wchar_t *text)
{
    auto rc = font->MeasureDrawBounds(text,DirectX::XMFLOAT2(0.0f,0.0f));
    return Rect(rc.right - rc.left,rc.bottom - rc.top,rc.left,rc.top);
}

Font2D::~Font2D()
{

}