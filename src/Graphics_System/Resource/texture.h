#pragma once

#include "resource.h"


class Texture : public Resource
{
public:
    Texture(const wchar_t* full_path, Resource_Manager* manager);
   

private:

   texture_internal_sptr texture;
   friend class Material;
};

