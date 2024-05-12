#include "graphics_engine.h"

#include <exception>

Graphics_Engine* Graphics_Engine::engine = nullptr;

Graphics_Engine::Graphics_Engine() {
    try {
        render_system = new Render_System();
    } catch(...){throw std::exception("Failed to create render system!");}

    try {
        texture_manager = new Texture_Manager();
    } catch(...){throw std::exception("Failed to create texture manager!");}

    try {
        mesh_manager = new Mesh_Manager();
    } catch(...){throw std::exception("Failed to create mesh manager!");}
    try {
        font_manager = new Font_Manager();
    } catch(...){throw std::exception("Failed to create font manager!");}
    void* shader_byte_code = nullptr;
    size_t shader_size = 0;

    render_system->compile_vertex_shader(L"C:/Users/zachm/OneDrive/Desktop/Moryx_engine/src/shaders/vert_mesh_layout.hlsl","main",&shader_byte_code,&shader_size);

    memcpy(layout_byte_code,shader_byte_code,shader_size);
    layout_size = shader_size;

    render_system->release_compiled_shader();

}

Graphics_Engine::~Graphics_Engine() {
    delete font_manager;
    delete mesh_manager;
    delete texture_manager;
    delete render_system;
    Graphics_Engine::engine = nullptr;
}

Render_System *Graphics_Engine::get_render_system() {
    return render_system;
}

Texture_Manager *Graphics_Engine::get_texture_manager() {
    return texture_manager;
}

Mesh_Manager *Graphics_Engine::get_mesh_manager() {
    return mesh_manager;
}

Font_Manager *Graphics_Engine::get_font_manager()
{
    return font_manager;
}

Graphics_Engine *Graphics_Engine::get_engine() {
    return engine;
}

void Graphics_Engine::create() {
    if(Graphics_Engine::engine) {throw std::exception("graphics engine already exists!");}
    Graphics_Engine::engine = new Graphics_Engine();
}

void Graphics_Engine::release() {
     if(!Graphics_Engine::engine) {return;}
     delete Graphics_Engine::engine;
}

void Graphics_Engine::get_vert_mesh_layout_shader_data(void **byte_code, size_t *size) {
    *byte_code = layout_byte_code;
    *size = layout_size;
}

material_sptr Graphics_Engine::create_material(const wchar_t *vert_shader_path, const wchar_t *pix_shader_path)
{
    material_sptr mptr {nullptr};
    try {
        mptr = std::make_shared<Material>(vert_shader_path,pix_shader_path);
    }
    catch(...) {}
    return mptr;
}

material_sptr Graphics_Engine::create_material(const material_sptr &material) {

   material_sptr mptr {nullptr};
    try {
        mptr = std::make_shared<Material>(material);
    }
    catch(...) {}
    return mptr;
}

void Graphics_Engine::set_material(const material_sptr &material) {
    render_system->set_rasterizer_sate(material->culling_mode == CULL_MODE::FRONT_CULLING);
    if(material->const_buffer) {
        render_system->get_device_context()->set_constant_buffer(material->vert_shader, material->const_buffer);
        render_system->get_device_context()->set_constant_buffer(material->pix_shader, material->const_buffer);
    }

    render_system->get_device_context()->set_vertex_shader(material->vert_shader);
    render_system->get_device_context()->set_pixel_shader(material->pix_shader);
    if(material->textures.size()) {
        render_system->get_device_context()->set_texture(material->pix_shader,&material->textures[0],(UINT)material->textures.size());
    }
}

void Graphics_Engine::update(Mesh_Data& mesh_data, const swapchain_sptr& swapchain) {
    //auto swapchain = display->swapchain;
    auto context = render_system->get_device_context();

    context->clear_render_target_color(swapchain, 1.0f,0.0f,0.0f,1.0f);
    auto win_size = display->get_client_size();
    context->set_viewport_size(win_size.width,win_size.height);

    Constant_Data const_data = {};
    const_data.world_camera.set_identity();
    const_data.cam_view.set_identity();
    const_data.cam_projection.set_identity();

    const_data.world_camera.set_rotation_y(0.707f);
    const_data.cam_view.set_translation(Vector3D(0.0f,0.0f,-10.0f));
    const_data.cam_view.inverse();

    const_data.cam_projection.set_perspective_FOV(1.3f,win_size.width/win_size.height,0.01f,1000.0f);

    context->set_vertex_buffer(mesh_data.mesh->get_vert_buffer());
    context->set_index_buffer(mesh_data.mesh->get_index_buffer());

    for(auto i = 0; i < mesh_data.mesh->get_num_materials();i++) {
        mesh_data.material->set_buffer_data(&const_data,sizeof(Constant_Data));

        context->set_constant_buffer(mesh_data.material->vert_shader,mesh_data.material->const_buffer);
        

        context->set_vertex_shader(mesh_data.material->vert_shader);
        context->set_pixel_shader(mesh_data.material->pix_shader);
        
        auto slot = mesh_data.mesh->get_material_slot((UINT)i);
       
        context->draw_indexed_triangle_list(slot.num_indeces,slot.start_index,0);


    }
    swapchain->present(true);
    
}
