#include "game.h"

#include "i_game_project_manager.h"

Game::Game() {
    input = std::make_unique<Input_System>();
    graphics = std::make_unique<Graphics_Engine>(this);
    display = std::make_unique<Display>(this);
    resource_manager = std::make_unique<Resource_Manager>(this);
    handler = std::make_unique<entity_handler>();
    
    mesh = resource_manager->create_resource_from_file<Mesh>(L"../../src/Assets/Meshes/house.obj");
    auto terrain = resource_manager->create_resource_from_file<Mesh>(L"../../src/Assets/Meshes/terrain.obj");
    auto tex = resource_manager->create_resource_from_file<Texture>(L"../../src/Assets/Textures/wood.jpg");
    material = resource_manager->create_resource_from_file<Material>(L"../../src/shaders/mono_shader.hlsl");
    material->add_texture(tex);
    auto floor = resource_manager->create_resource_from_file<Texture>(L"../../src/Assets/Textures/Sponza/sponza_floor_a_diff.jpg");
    auto fmat = resource_manager->create_resource_from_file<Material>(L"../../src/shaders/mono_shader.hlsl");
    fmat->add_texture(floor);

    {
        auto sky_mesh = resource_manager->create_resource_from_file<Mesh>(L"../../src/Assets/Meshes/sphere.obj");
        auto sky_tex = resource_manager->create_resource_from_file<Texture>(L"../../src/Assets/Textures/sky.jpg");
        auto sky_mat = resource_manager->create_resource_from_file<Material>(L"../../src/shaders/test_vert.hlsl");
        sky_mat->add_texture(sky_tex);
        sky_mat->set_culling_mode(CULL_MODE::FRONT_CULLING);

        auto sky = handler->create_entity("sky box");
        sky.add<Transform>();
        sky.get_ref<Transform>()->scale = Vector3D(100.0f,100.0f,100.0f);
        sky.get_ref<Transform>()->compute_world_matrix();
        handler->register_mesh(sky);
        sky.get_ref<M_Mesh>()->mesh = sky_mesh;
        sky.get_ref<M_Mesh>()->materials.push_back(sky_mat);
    }

    {
        auto light = handler->create_light("light 1");
        light.get_ref<Transform>()->rotation = Vector3D(0.5f,0.5f,0.0f);
        light.get_ref<Transform>()->position = Vector3D(0.0f,10.0f,20.0f);
        light.get_ref<Transform>()->compute_world_matrix();

        light.get_ref<Light>()->color = Vector4D(1.0f,0.0f,0.0f,1.0f);

    }

    auto n = handler->create_entity("floor");
    n.add<Transform>();
    n.get_ref<Transform>()->compute_world_matrix();
    handler->register_mesh(n);
    n.get_ref<M_Mesh>()->mesh = terrain;
    n.get_ref<M_Mesh>()->materials.push_back(fmat);

    input->set_lock_area(display->get_client_size());
   
    player = handler->create_entity("player");
    player.add<Transform>();
    player.get_ref<Transform>()->position = Vector3D(1.0f,0.0f,0.0f);
    player.get_ref<Transform>()->compute_world_matrix();

    handler->register_mesh(player);
    player.get_ref<M_Mesh>()->mesh = resource_manager->create_resource_from_file<Mesh>(L"../../src/Assets/Meshes/house.obj");
    player.get_ref<M_Mesh>()->materials.push_back(material);
    player.get_ref<M_Mesh>()->materials.push_back(material);
    player.get_ref<M_Mesh>()->materials.push_back(material);
    player.get_ref<M_Mesh>()->materials.push_back(material);

    cam = handler->create_camera("cam 1");
    cam.get_ref<Transform>()->position = Vector3D(0.0f,0.0f,-10.0f);
    cam.get_ref<Transform>()->rotation = Vector3D(0.0f,0.0f,0.0f);
    cam.get_ref<Transform>()->compute_world_matrix();
    cam.get_ref<Camera>()->far_plane = 2000;
    //MORYX_INFO("pos X: " <<player.get<Transform>()->position.x<<" Y: " <<player.get<Transform>()->position.y << " Z: "<<player.get<Transform>()->position.z);
    
    text = handler->create_text("text 1");
    text.get_ref<Transform>()->position = Vector3D(0.0f,0.0f,0.0f);
    text.get_ref<Text>()->text = L"Testing Text";
    text.get_ref<Text>()->font = resource_manager->create_resource_from_file<Font>(L"../../src/Assets/Fonts/Bahnschrift.font");
    
    input->lock_cursor(true);
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
    if(input->is_key_down(Key::W)) {
       
       cam_pos.z += cam.get_ref<Transform>()->world_matrix.get_z_direction().z ;
       cam_pos.x += cam.get_ref<Transform>()->world_matrix.get_z_direction().x ;
       cam_pos.y += cam.get_ref<Transform>()->world_matrix.get_z_direction().y ;
    }
    if(input->is_key_down(Key::S)) {
       cam_pos.z -= cam.get_ref<Transform>()->world_matrix.get_z_direction().z ;
       cam_pos.x -= cam.get_ref<Transform>()->world_matrix.get_z_direction().x ;
       cam_pos.y -= cam.get_ref<Transform>()->world_matrix.get_z_direction().y ;
    }
    if(input->is_key_down(Key::A)) {
       cam_pos.z -= cam.get_ref<Transform>()->world_matrix.get_x_direction().z ;
       cam_pos.x -= cam.get_ref<Transform>()->world_matrix.get_x_direction().x ;
       cam_pos.y -= cam.get_ref<Transform>()->world_matrix.get_x_direction().y ;
    }
    if(input->is_key_down(Key::D)) {
       cam_pos.z += cam.get_ref<Transform>()->world_matrix.get_x_direction().z ;
       cam_pos.x += cam.get_ref<Transform>()->world_matrix.get_x_direction().x ;
       cam_pos.y += cam.get_ref<Transform>()->world_matrix.get_x_direction().y ;
    }
    if(input->is_key_down(Key::SPACE)) {
       cam_pos.y += 1;
    }
    if(input->is_key_down(Key::SHIFT)) {
       cam_pos.y -= 1;
    }

    int FPS = (1/delta_time);


    text.get_ref<Text>()->text = std::to_wstring(FPS);

    auto d_pos = input->get_delta_mouse_pos();
    //MORYX_INFO("Mouse X_pos: " << d_pos.x << " || Mouse Y_pos: "<< d_pos.y);

    //player.get_ref<Transform>()->rotation = Vector3D(0.0f,d_pos.x * delta_time,0.0f);
    //handler->bind_transform_to_mesh(player);
    rot_y += d_pos.x * 0.001f;
    rot_x += d_pos.y * 0.001f;

    cam.get_ref<Transform>()->rotation = Vector3D(rot_x,rot_y,0.0f);
    cam.get_ref<Transform>()->position = cam_pos;
    cam.get_ref<Transform>()->compute_world_matrix();
   
    graphics->update();
}

void Game::quit() {
    is_running = false;
}