#include "font.h"
#include "../Graphics/graphics_engine.h"
#include <sstream>
#include <regex>
#include <filesystem>

Font::Font(const wchar_t *file_path, Resource_Manager* manager): Resource(file_path,manager) {
    
    auto render_sys = manager->get_game()->get_graphics_engine()->get_render_system();
    font = render_sys->create_font(file_path);
}

const font_internal_sptr& Font::get_font()
{
    return font;
}

bool Font_Utility::create_font(const wchar_t *font_name, float font_size, const wchar_t *output_path) {
    std::wstringstream stream;
    std::wstring string = std::regex_replace(font_name,std::wregex(L"\\s+"),L"");

    stream << output_path << string << ".font";

    if(!std::filesystem::exists(stream.str())) {
        std::wstringstream command;
       
        command << "C:/Users/zachm/OneDrive/Desktop/Moryx_engine/lib/DirectXTK/bin/MakeSpriteFont ";
        command << "\"" << font_name << "\" ";
        command << stream.str() << " ";
        command << "/FontSize:" << font_size;

        if(_wsystem(command.str().c_str()) != 0) {
            MORYX_ERROR("Failed to create font!");
        }
        return true;
    }
    return true;
}