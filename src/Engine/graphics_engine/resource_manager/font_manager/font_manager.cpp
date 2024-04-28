#include "font_manager.h"

Font_Manager::Font_Manager():Resource_Manager()
{

}

Font_Manager::~Font_Manager()
{

}

font_sptr Font_Manager::create_font_from_file(const wchar_t *file_path)
{
    return std::static_pointer_cast<Font>(create_resource_from_file(file_path));
}

Resource *Font_Manager::create_resource_from_file_concrete(const wchar_t *file_path)
{
   Font* font = nullptr;
    try{
        font = new Font(file_path);
    } catch(...){}

    return font;
}
