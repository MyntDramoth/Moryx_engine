#pragma once

#include "resource.h"
#include <vector>
//#include "../Math/rect.h"
#include "../Graphics/Render_System/Texture/texture_internal.h"

class Texture : public Resource
{
public:
    Texture(const wchar_t* full_path, Resource_Manager* manager);
    Texture(const Rect& size, Texture_Internal::Texture_Type tex_type, Resource_Manager* manager, uint32_t array_size = 1);
    void populate_texture_array(std::vector<const wchar_t*> files) {texture->populate_texture_array(files);}
private:

   texture_internal_sptr texture;
   friend class Material;
   friend class Graphics_Engine;
};

