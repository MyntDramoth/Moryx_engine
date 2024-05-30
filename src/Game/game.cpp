#include "game.h"
#include "../Graphics_System/Graphics/Render_System/Constant_Buffer/constant_buffer.h"


Game::Game() {
    graphics = std::make_unique<Graphics_Engine>(this);
    display = std::make_unique<Display>(this);
    resource_manager = std::make_unique<Resource_Manager>(this);

    mesh = resource_manager->create_resource_from_file<Mesh>(L"../../src/Assets/Meshes/house.obj");
    auto tex = resource_manager->create_resource_from_file<Texture>(L"../../src/Assets/Textures/wood.jpg");
    material = resource_manager->create_resource_from_file<Material>(L"../../src/shaders/test_vert.hlsl");
    material->add_texture(tex);
}



Game::~Game() {

}

void Game::on_display_size_change(const Rect &size) {
    on_update_internal();
}

void Game::on_update_internal()
{
    graphics->update({mesh,material});
}

void Game::quit() {
    is_running = false;
}