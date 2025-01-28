#include "graphics_engine.h"

#include <exception>
#include "../../Game/game.h"
#include "../../Game/display.h"

#include "../Resource/font.h"
#include "Render_System/Font/font_internal.h"


struct Light_Data {
    Vector4D color;
    Vector4D direction;
};

__declspec(align(16))
struct Const_Buff {
    Matrix4x4 world_space;
    Matrix4x4 view_space;
    Matrix4x4 projection;
    Vector4D camera_position;
    Light_Data light;
};

Graphics_Engine::Graphics_Engine(Game* game): game(game) {
    render_system = std::make_unique<Render_System>();

}

Graphics_Engine::~Graphics_Engine() {
   
   
}

Render_System *Graphics_Engine::get_render_system() {
    return render_system.get();
}

void Graphics_Engine::update(float delta_time) {
    auto swapchain = game->display->swapchain;
    auto context = render_system->get_device_context();
    auto entity_system = game->get_entity_handler();

    context->clear_render_target_color(swapchain, 0.0f,0.0f,0.0f,1.0f);
    auto win_size = game->display->get_client_size();
    context->set_viewport_size(win_size.width,win_size.height);

    Vector2D atlas = Vector2D(1/8.0f,1/8.0f);

    Const_Buff const_data = {};
    std::vector<Instance_Data> inst_data = {};

    for(auto cam_entity : entity_system->get_cams()) {
        auto cam = cam_entity.second.get_ref<Camera>();
        auto tr = cam_entity.second.get_mut<Transform>();
        cam->screen_area = win_size;
        cam->compute_projection_matrtix();
        const_data.view_space = cam->get_view(*tr);
        const_data.projection = cam->projection_matrix;
        const_data.camera_position = tr->position;
    }

    for(auto light_entity : entity_system->get_lights()) {
        auto light = light_entity.second.get_ref<Light>();
        auto transform = light_entity.second.get_ref<Transform>();

        const_data.light.direction = transform->world_matrix.get_z_direction();
        const_data.light.color = light->color;
    }

    for(auto mesh_entity : entity_system->get_meshes()) {
        auto mesh = mesh_entity.second.get_ref<M_Mesh>();
        auto transform = mesh_entity.second.get_mut<Transform>();
        const_data.world_space =  transform->world_matrix;
        const auto materials = mesh->materials;


        context->set_vertex_buffer(mesh->mesh->vertex_buffer);
        context->set_index_buffer(mesh->mesh->index_buffer);
    
        

        for(auto i = 0; i < mesh->mesh->get_num_materials();i++) {
        
            if(i >= materials.size()) {break;}
            auto mat = materials[i];

            render_system->set_cull_mode(mat->get_culling_mode());

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

    //====================
    // Instance Rendering
    //====================
    /*
    for(float x = 0.0f; x < 100.0f;x++) {
        for(float y = 0.0f; y < 100.0f;y++) {
            float var;
            float blck = 1.0f;
            //for (float z = 0.0f; z < 10.0f;z++) {
                //var = fnSimplex->GenSingle3D(x,y,1,12121);
                //var = rand() % 64 + 1;
            //}
             //auto var = rand() % 64 + 1;
             //var = fnSimplex->GenSingle3D(x,y,1,12121);
             //if(var < 0.6f) {
              //  blck = 2.0f;
            //}
            
           
           // if(output[(int)(x+y)] < 0.05f) {blck = 2.0f;}
            inst_data.push_back({Vector3D(x,1.0f,y),atlas,Vector2D((blck/8.0f),(blck/8.0f))});
        }
    }*/
    
    //inst_data = *game->get_instance_data();
    for(auto inst_entity : entity_system->get_instances()) {
        auto mesh = inst_entity.second.get_ref<M_Mesh>();
        
        mesh->mesh->inst_buffer->UpdateInstanceBuffer(context, /*inst_data*/ game->get_instance_data());
        auto transform = inst_entity.second.get_mut<Transform>();
        const_data.world_space =  transform->world_matrix;
        const auto materials = mesh->materials;
        
        context->set_instance_and_vertex_buffer(mesh->mesh->vertex_buffer,mesh->mesh->inst_buffer);
        context->set_index_buffer(mesh->mesh->index_buffer);
    
        

        for(auto i = 0; i < mesh->mesh->get_num_materials();i++) {
        
            if(i >= materials.size()) {break;}
            auto mat = materials[i];

            render_system->set_cull_mode(mat->get_culling_mode());

            mat->set_buffer_data(&const_data,sizeof(Const_Buff));

            context->set_constant_buffer(mat->vert_shader,mat->const_buffer);
            context->set_constant_buffer(mat->pix_shader,mat->const_buffer);
            
            context->set_vertex_shader(mat->vert_shader);
            context->set_pixel_shader(mat->pix_shader);
            
            context->set_texture(&mat->textures[0],mat->textures.size());

            auto slot = mesh->mesh->get_material_slot((UINT)i);
            auto inst_slot = mesh->mesh->get_inst_slot();
            context->draw_indexed_instanced(slot.num_indeces, inst_slot.num_instances, slot.start_index,0,inst_slot.start_index);


        }
    }

    //==========
    // GUI Rendering
    //==========

    for(auto image_entity : entity_system->get_images()) {
        auto image = image_entity.second.get_ref<Image>();
        auto pos = image_entity.second.get_ref<Transform>()->position;
        auto size = image->size;
        render_system->draw_image(image->image->texture,{size.width,size.height,(int)pos.x,(int)pos.y});
    }

    for(auto sprite_entity : entity_system->get_sprites()) {
        auto sprites = sprite_entity.second.get_ref<Animation_2D>();
        auto pos = sprite_entity.second.get_ref<Transform>()->position;
        auto size = sprites->size;
        auto index = sprites->sprite_index;
        sprites->current_frame_time -= delta_time;
        if(sprites->current_frame_time <= 0) {
            sprites->sprite_index += 1;
            sprites->current_frame_time = sprites->duration;
        }
        if((int)sprites->sprite_index == (int)sprites->sprites.size()){
            sprites->sprite_index = 0;
        }
        render_system->draw_image(sprites->sprites[sprites->sprite_index]->texture,{size.width,size.height,(int)pos.x,(int)pos.y});     
    }

    for(auto text_entity : entity_system->get_text()) {
        auto text = text_entity.second.get_ref<Text>();
        auto transform = text_entity.second.get_ref<Transform>();
        auto font = text->font->get_font();

        font->batch->Begin();
        font->font->DrawString(font->batch.get(),text->text.c_str(),DirectX::XMFLOAT2(transform->position.x,transform->position.y));
        font->batch->End();
    }


    swapchain->present(false);
    render_system->clear_state();
}
