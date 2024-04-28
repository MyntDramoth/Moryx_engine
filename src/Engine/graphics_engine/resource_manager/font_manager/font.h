#pragma once
#include "../resource.h"
#include "../../prerequisites.h"
#include <exception>

class Font : public Resource {
public:
    Font(const wchar_t* file_path);
    const font2D_sptr& get_font();
private:
    font2D_sptr font;
};

class Font_Utility {
public:
    bool create_font(const wchar_t* font_name, float font_size, const wchar_t* output_path);
};