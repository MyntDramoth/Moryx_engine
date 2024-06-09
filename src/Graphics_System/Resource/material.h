#pragma once

#include "resource.h"
#include "resource_manager.h"
#include <vector>
#include "../prerequisites.h"

class Material : public Resource
{
public:
    Material(const wchar_t* shader_path, Resource_Manager* manager);
    Material(const material_sptr& material, Resource_Manager* manager);
    ~Material();

    void add_texture(const texture_sptr& texture);
    void remove_texture(UINT index);

    void set_buffer_data(void* data, UINT data_size);
    void set_culling_mode(CULL_MODE mode);
    CULL_MODE get_culling_mode();
    
private:
    vert_shader_sptr vert_shader;
    pix_shader_sptr pix_shader;
    const_buffer_sptr const_buffer;

    std::vector<texture_internal_sptr> textures;
    CULL_MODE culling_mode = CULL_MODE::BACK_CULLING;

    friend class Graphics_Engine;

};
