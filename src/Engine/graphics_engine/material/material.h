#pragma once

#include "../pixel_shader/pixel_shader.h"
#include "../vertex_shader/vertex_shader.h"

#include "../constant_buffer/constant_buffer.h"

#include <vector>

enum CULL_MODE {
    FRONT_CULLING = 0,
    BACK_CULLING
};

class Graphics_Engine;

class Material
{
public:
    Material(const wchar_t* vert_shader_path, const wchar_t* pix_shader_path);
    Material(const material_sptr& material);
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

    std::vector<texture_sptr> textures;

    CULL_MODE culling_mode = BACK_CULLING;

    friend class Graphics_Engine;

};
