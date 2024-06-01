#include "game.h"
#include "../Graphics_System/Graphics/Render_System/Constant_Buffer/constant_buffer.h"


Game::Game() {
    input = std::make_unique<Input_System>();
    graphics = std::make_unique<Graphics_Engine>(this);
    display = std::make_unique<Display>(this);
    resource_manager = std::make_unique<Resource_Manager>(this);

    mesh = resource_manager->create_resource_from_file<Mesh>(L"../../src/Assets/Meshes/house.obj");
    auto tex = resource_manager->create_resource_from_file<Texture>(L"../../src/Assets/Textures/wood.jpg");
    material = resource_manager->create_resource_from_file<Material>(L"../../src/shaders/test_vert.hlsl");
    material->add_texture(tex);

    input->set_lock_area(display->get_client_size());
    //input->lock_cursor(true);
}



Game::~Game() {

}

void Game::on_display_size_change(const Rect &size) {
    input->set_lock_area(display->get_client_size());
    on_update_internal();
}

void Game::on_update_internal()
{
    input->update();

    if(input->is_key_up(Key::ESCAPE)) {
        quit();
    }
    if(input->is_key_up(Key::ENTER)) {
       input->lock_cursor(true);
    }

    auto d_pos = input->get_delta_mouse_pos();
    //MORYX_INFO("Mouse X_pos: " << d_pos.x << " || Mouse Y_pos: "<< d_pos.y);

    graphics->update({mesh,material});
}

void Game::quit() {
    is_running = false;
}