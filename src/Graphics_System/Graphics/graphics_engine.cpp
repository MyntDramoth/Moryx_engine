#include "graphics_engine.h"

#include <exception>
#include "../../Game/game.h"
#include "../../Game/display.h"


__declspec(align(16))
struct Const_Buff {
    Matrix4x4 world_space;
    Matrix4x4 view_space;
    Matrix4x4 projection;
};

Graphics_Engine::Graphics_Engine(Game* game): game(game) {
    render_system = std::make_unique<Render_System>();

}

Graphics_Engine::~Graphics_Engine() {
   
   
}

Render_System *Graphics_Engine::get_render_system() {
    return render_system.get();
}

void Graphics_Engine::update() {
    auto swapchain = game->display->swapchain;
    auto context = render_system->get_device_context();
    auto entity_system = game->get_entity_handler();

    context->clear_render_target_color(swapchain, 1.0f,0.0f,0.0f,1.0f);
    auto win_size = game->display->get_client_size();
    context->set_viewport_size(win_size.width,win_size.height);

    Const_Buff const_data = {};
    //const_data.world_space.set_identity();
    const_data.view_space.set_identity();
    const_data.projection.set_identity();

    //const_data.world_space.set_rotation_y(0.707f);
    const_data.view_space.set_translation(Vector3D(0.0f,0.0f,-10.0f));
    const_data.view_space.inverse();

  
    //const_data.projection.set_perspective_FOV(1.57f,((float)win_size.width/(float)win_size.height),0.1f,100.0f);
    const_data.projection.set_perspective_FOV(1.3f,((float)win_size.width/(float)win_size.height),0.01f,1000.0f);
   
    for(auto mesh_entity : entity_system->get_meshes()) {
        auto mesh = mesh_entity.second.get_ref<M_Mesh>();
        auto transform = mesh_entity.second.get_ref<Transform>();
        const_data.world_space =  transform->world_matrix;
        const auto materials = mesh->materials;


        context->set_vertex_buffer(mesh->mesh->vertex_buffer);
        context->set_index_buffer(mesh->mesh->index_buffer);
    

        for(auto i = 0; i < mesh->mesh->get_num_materials();i++) {
        
            if(i >= materials.size()) {break;}
            auto mat = materials[i];
            mat->set_buffer_data(&const_data,sizeof(Const_Buff));

            context->set_constant_buffer(mat->vert_shader,mat->const_buffer);
            context->set_constant_buffer(mat->pix_shader,mat->const_buffer);
            
            context->set_vertex_shader(mat->vert_shader);
            context->set_pixel_shader(mat->pix_shader);
            
            context->set_texture(&mat->textures[0],mat->textures.size());

            auto slot = mesh->mesh->get_material_slot((UINT)i);
        
            context->draw_indexed_triangle_list(slot.num_indeces,slot.start_index,0);


        }
    }
    swapchain->present(true);
    
}
