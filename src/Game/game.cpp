#include "game.h"
#include "../Graphics_System/Graphics/Render_System/Constant_Buffer/constant_buffer.h"


Game::Game() {
    input = std::make_unique<Input_System>();
    graphics = std::make_unique<Graphics_Engine>(this);
    display = std::make_unique<Display>(this);
    resource_manager = std::make_unique<Resource_Manager>(this);
    handler = std::make_unique<entity_handler>();
    
    mesh = resource_manager->create_resource_from_file<Mesh>(L"../../src/Assets/Meshes/house.obj");
    auto tex = resource_manager->create_resource_from_file<Texture>(L"../../src/Assets/Textures/wood.jpg");
    material = resource_manager->create_resource_from_file<Material>(L"../../src/shaders/test_vert.hlsl");
    material->add_texture(tex);

    input->set_lock_area(display->get_client_size());
    //input->lock_cursor(true);
    player = handler->create_entity("player");
    player.add<Transform>();
    player.get_ref<Transform>()->position = Vector3D(0.0f,0.0f,0.0f);
    handler->bind_transform_to_mesh(player);

    handler->register_mesh(player);
    player.get_ref<M_Mesh>()->mesh = resource_manager->create_resource_from_file<Mesh>(L"../../src/Assets/Meshes/house.obj");
    player.get_ref<M_Mesh>()->materials.push_back(material);
    player.get_ref<M_Mesh>()->materials.push_back(material);
    player.get_ref<M_Mesh>()->materials.push_back(material);
    player.get_ref<M_Mesh>()->materials.push_back(material);
    //MORYX_INFO("pos X: " <<player.get<Transform>()->position.x<<" Y: " <<player.get<Transform>()->position.y << " Z: "<<player.get<Transform>()->position.z);
}



Game::~Game() {

}

void Game::on_display_size_change(const Rect &size) {
    input->set_lock_area(display->get_client_size());
    on_update_internal();
}

void Game::on_update_internal()
{

    auto current_time = std::chrono::system_clock::now();
    auto elapsed_time = std::chrono::duration<double>();
    if(previous_time.time_since_epoch().count()) {
        elapsed_time = current_time - previous_time;  
    }
    previous_time = current_time;

    auto delta_time = (float)elapsed_time.count();
    input->update();
    handler->purge_entities(delta_time);
    if(input->is_key_up(Key::ESCAPE)) {
        quit();
    }
    if(input->is_key_up(Key::ENTER)) {
       input->lock_cursor(true);
    }

    auto d_pos = input->get_delta_mouse_pos();
    //MORYX_INFO("Mouse X_pos: " << d_pos.x << " || Mouse Y_pos: "<< d_pos.y);

    //player.get_ref<Transform>()->rotation = Vector3D(0.0f,d_pos.x * delta_time,0.0f);
    //handler->bind_transform_to_mesh(player);

    graphics->update();
}

void Game::quit() {
    is_running = false;
}