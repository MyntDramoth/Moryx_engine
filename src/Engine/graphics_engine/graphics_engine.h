#pragma once

#include "prerequisites.h"

#include "render_system/render_system.h"
#include "resource_manager/texture_manager/texture_manager.h"
#include "resource_manager/mesh_manager/mesh_manager.h"
#include "resource_manager/font_manager/font_manager.h"

#include "material/material.h"

class Graphics_Engine {
public:
    
    Render_System* get_render_system();
    Texture_Manager* get_texture_manager();
    Mesh_Manager* get_mesh_manager();
    Font_Manager* get_font_manager();
    static Graphics_Engine* get_engine();
    static void create();
    static void release();
    
    void get_vert_mesh_layout_shader_data(void** byte_code, size_t* size);

    material_sptr create_material(const wchar_t* vert_shader_path, const wchar_t* pix_shader_path);
    material_sptr create_material(const material_sptr& material);
    void set_material(const material_sptr& material);
    
private:
    //these are private because the class is a singleton
    Graphics_Engine();
    ~Graphics_Engine();
    Render_System* render_system = nullptr;
    Texture_Manager* texture_manager = nullptr;
    Mesh_Manager* mesh_manager = nullptr;
    Font_Manager* font_manager = nullptr;
    static Graphics_Engine* engine;

    unsigned char layout_byte_code[1024];
    size_t layout_size = 0;
    
};