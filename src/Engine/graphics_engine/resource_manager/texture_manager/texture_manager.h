#pragma once

#include "../resource_manager.h"
#include "texture.h"

class Texture_Manager : public Resource_Manager
{
public:
    Texture_Manager();
    ~Texture_Manager();
    texture_sptr create_texture_from_file(const wchar_t* file_path);

protected:

    virtual Resource* create_resource_from_file_concrete(const wchar_t* file_path);

private:

};