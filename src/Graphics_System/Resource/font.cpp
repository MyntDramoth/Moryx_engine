// #include "font.h"
// #include "../Graphics/graphics_engine.h"
// #include <sstream>
// #include <regex>
// #include <filesystem>

// Font::Font(const wchar_t *file_path): Resource(file_path) {
//     font = Graphics_Engine::get_engine()->get_render_system()->create_font(file_path);
// }

// const font2D_sptr &Font::get_font()
// {
//     return font;
// }

// bool Font_Utility::create_font(const wchar_t *font_name, float font_size, const wchar_t *output_path) {
//     std::wstringstream stream;
//     std::wstring string = std::regex_replace(font_name,std::wregex(L"\\s+"),L"");

//     stream << output_path << string << ".font";

//     if(!std::filesystem::exists(stream.str())) {
//         std::wstringstream command;
       
//         command << "C:/Users/zachm/OneDrive/Desktop/Moryx_engine/lib/DirectXTK/bin/MakeSpriteFont ";
//         command << "\"" << font_name << "\" ";
//         command << stream.str() << " ";
//         command << "/FontSize:" << font_size;

//         if(_wsystem(command.str().c_str()) != 0) {
//             throw std::exception("Failed to create font!");
//         }
//         return true;
//     }
//     return true;
// }


// #include "../render_system/render_system.h"

// Font2D::Font2D(const wchar_t* file_path, Render_System* render_system) {
   
//     font = std::make_unique<DirectX::DX11::SpriteFont>(render_system->device,file_path);
//     if(!font) {
//         throw std::exception("Failed to create Font!");
//     }

//     auto context = render_system->device_context;
//     batch = std::make_unique<DirectX::DX11::SpriteBatch>(context->get_context());
//      if(!batch) {
//         throw std::exception("Failed to create Font!");
//     }

// }

// Rect Font2D::get_bounds(const wchar_t *text)
// {
//     auto rc = font->MeasureDrawBounds(text,DirectX::XMFLOAT2(0.0f,0.0f));
//     return Rect(rc.right - rc.left,rc.bottom - rc.top,rc.left,rc.top);
// }

// Font2D::~Font2D()
// {

// }