// #pragma once
// #include "resource.h"
// #include "../prerequisites.h"
// #include <exception>

// class Font : public Resource {
// public:
//     Font(const wchar_t* file_path);
//     const font2D_sptr& get_font();
// private:
//     font2D_sptr font;
// };

// class Font_Utility {
// public:
//     bool create_font(const wchar_t* font_name, float font_size, const wchar_t* output_path);
// };

// #include "../prerequisites.h"

// #include <SpriteFont.h>
// #include <exception>
// #include "../Math/rect.h"

// class App_Window;
// class Font2D
// {
// public:
//     Font2D(const wchar_t* file_path, Render_System* render_system);
//     Rect get_bounds(const wchar_t* text);
//     ~Font2D();

// private:
//     std::unique_ptr<DirectX::DX11::SpriteFont> font {nullptr};
//     std::unique_ptr<DirectX::DX11::SpriteBatch> batch {nullptr};

//     Render_System* system {nullptr};
//     friend class App_Window;
// };