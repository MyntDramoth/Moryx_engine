#pragma once
#include "../resource_manager.h"
#include "font.h"

class Font_Manager: public Resource_Manager
{
public:
    Font_Manager();
    ~Font_Manager();
    font_sptr create_font_from_file(const wchar_t* file_path);
    //texture_sptr create_texture(const Rect& size, Texture::Texture_Type tex_type);

protected:

    virtual Resource* create_resource_from_file_concrete(const wchar_t* file_path);
private:

};