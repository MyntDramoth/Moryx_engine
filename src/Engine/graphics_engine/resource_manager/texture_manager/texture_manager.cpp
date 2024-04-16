#include "texture_manager.h"

Texture_Manager::Texture_Manager(): Resource_Manager() {

}

Texture_Manager::~Texture_Manager() {

}

texture_sptr Texture_Manager::create_texture_from_file(const wchar_t *file_path)
{
    return std::static_pointer_cast<Texture>(create_resource_from_file(file_path));
}

texture_sptr Texture_Manager::create_texture(const Rect &size, Texture::Texture_Type tex_type) {
    Texture* tex = nullptr;
    try{
        tex = new Texture(size,tex_type);
    } catch(...){}

    texture_sptr res(tex);
    return res;
}

Resource *Texture_Manager::create_resource_from_file_concrete(const wchar_t *file_path)
{
    Texture* tex = nullptr;
    try{
        tex = new Texture(file_path);
    } catch(...){}

    return tex;
}
