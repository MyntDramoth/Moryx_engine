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

void Graphics_Engine::update(const Mesh_Data& mesh_data) {
    auto swapchain = game->display->swapchain;
    auto context = render_system->get_device_context();

    context->clear_render_target_color(swapchain, 1.0f,0.0f,0.0f,1.0f);
    auto win_size = game->display->get_client_size();
    context->set_viewport_size(win_size.width,win_size.height);

    Const_Buff const_data = {};
    const_data.world_space.set_identity();
    const_data.view_space.set_identity();
    const_data.projection.set_identity();

    const_data.world_space.set_rotation_y(0.707f);
    const_data.view_space.set_translation(Vector3D(0.0f,0.0f,-10.0f));
    const_data.view_space.inverse();

  
    //const_data.projection.set_perspective_FOV(1.57f,((float)win_size.width/(float)win_size.height),0.1f,100.0f);
   const_data.projection.set_perspective_FOV(1.3f,((float)win_size.width/(float)win_size.height),0.01f,1000.0f);
   
    
    context->set_vertex_buffer(mesh_data.mesh->vertex_buffer);
    context->set_index_buffer(mesh_data.mesh->index_buffer);
   

    for(auto i = 0; i < mesh_data.mesh->get_num_materials();i++) {
       
        mesh_data.material->set_buffer_data(&const_data,sizeof(Const_Buff));

        context->set_constant_buffer(mesh_data.material->vert_shader,mesh_data.material->const_buffer);
        context->set_constant_buffer(mesh_data.material->pix_shader,mesh_data.material->const_buffer);
        
        context->set_vertex_shader(mesh_data.material->vert_shader);
        context->set_pixel_shader(mesh_data.material->pix_shader);
        
        context->set_texture(&mesh_data.material->textures[0],mesh_data.material->textures.size());

        auto slot = mesh_data.mesh->get_material_slot((UINT)i);
       
        context->draw_indexed_triangle_list(slot.num_indeces,slot.start_index,0);


    }
    swapchain->present(true);
    
}
