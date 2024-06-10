#pragma once
#include "resource.h"
#include "resource_manager.h"
#include "../prerequisites.h"


class Font : public Resource {
public:
    Font(const wchar_t* file_path, Resource_Manager* manager);
    const font_internal_sptr& get_font();
private:
    font_internal_sptr font;
};

class Font_Utility {
public:
    bool create_font(const wchar_t* font_name, float font_size, const wchar_t* output_path);
};