#include "texture_manager.h"

Texture_Manager::Texture_Manager(): Resource_Manager() {

}

Texture_Manager::~Texture_Manager() {

}

texture_sptr Texture_Manager::create_texture_from_file(const wchar_t *file_path)
{
    return std::static_pointer_cast<Texture>(create_resource_from_file(file_path));
}

Resource *Texture_Manager::create_resource_from_file_concrete(const wchar_t *file_path)
{
    Texture* tex = nullptr;
    try{
        tex = new Texture(file_path);
    } catch(...){}

    return tex;
}
