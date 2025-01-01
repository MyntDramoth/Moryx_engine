#include "game.h"

#include "i_game_project_manager.h"

#include "../Game_Directories/Kore/chunk_generator.h"
#include <FastNoise/FastNoise.h>

Game::Game() {
    input = std::make_unique<Input_System>();
    graphics = std::make_unique<Graphics_Engine>(this);
    display = std::make_unique<Display>(this);
    resource_manager = std::make_unique<Resource_Manager>(this);
    handler = std::make_unique<entity_handler>();
    physics = std::make_unique<Physics>();

    //=====================//
    // IMPORTANT RESOURCES //
    //=====================//
    auto pallete = resource_manager->create_resource_from_file<Texture>(L"../../src/Game_Directories/Kore/Assets/Textures/color_pallete.png");


    //tile_mesh = resource_manager->create_resource_from_file<Mesh>(L"../../src/Assets/Meshes/plane.obj");

    //=====================//
    // TEMP RESOURCES      //
    //=====================//
    mesh = resource_manager->create_resource_from_file<Mesh>(L"../../src/Assets/Meshes/house.obj");
    auto terrain = resource_manager->create_resource_from_file<Mesh>(L"../../src/Assets/Meshes/terrain.obj");
    auto tex = resource_manager->create_resource_from_file<Texture>(L"../../src/Assets/Textures/wood.jpg");
    material = resource_manager->create_resource_from_file<Material>(L"../../src/shaders/mono_shader.hlsl");
    material->add_texture(tex);
    auto floor = resource_manager->create_resource_from_file<Texture>(L"../../src/Assets/Textures/Sponza/sponza_floor_a_diff.jpg");
    auto fmat = resource_manager->create_resource_from_file<Material>(L"../../src/shaders/mono_shader.hlsl");
    fmat->add_texture(pallete);

    {
        auto sky_mesh = resource_manager->create_resource_from_file<Mesh>(L"../../src/Assets/Meshes/sphere.obj");
        auto sky_tex = resource_manager->create_resource_from_file<Texture>(L"../../src/Assets/Textures/sky.jpg");
        auto sky_mat = resource_manager->create_resource_from_file<Material>(L"../../src/shaders/mono_shader.hlsl");
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
    
    auto image = handler->create_UI_image("UI 1");
    image.get_ref<Transform>()->position = Vector3D(50.0f,0.0f,0.0f);
    image.get_ref<Image>()->image = resource_manager->create_resource_from_file<Texture>(L"../../src/Assets/Textures/UI/cross.png");
    image.get_ref<Image>()->size = {50,50,0,0};

    auto anim = handler->create_animated_sprite("bettle");
    anim.get_ref<Transform>()->position = Vector3D(100.0f,0.0f,0.0f);
    anim.get_ref<Animation_2D>()->size = {50,50,0,0};
    anim.get_ref<Animation_2D>()->sprites.push_back( resource_manager->create_resource_from_file<Texture>(L"../../src/Game_Directories/Kore/Assets/Textures/TEMP/Characters/Chibi_Enemies_Pack/Sprites/Bettle/bettle1.png"));
    //image.get_ref<Animation_2D>()->sprites.push_back(bettle);
    auto bettle = resource_manager->create_resource_from_file<Texture>(L"../../src/Game_Directories/Kore/Assets/Textures/TEMP/Characters/Chibi_Enemies_Pack/Sprites/Bettle/bettle2.png");
    anim.get_ref<Animation_2D>()->sprites.push_back(bettle);
    bettle = resource_manager->create_resource_from_file<Texture>(L"../../src/Game_Directories/Kore/Assets/Textures/TEMP/Characters/Chibi_Enemies_Pack/Sprites/Bettle/bettle3.png");
    anim.get_ref<Animation_2D>()->sprites.push_back(bettle);
    bettle = resource_manager->create_resource_from_file<Texture>(L"../../src/Game_Directories/Kore/Assets/Textures/TEMP/Characters/Chibi_Enemies_Pack/Sprites/Bettle/bettle4.png");
    anim.get_ref<Animation_2D>()->sprites.push_back(bettle);
    anim.get_ref<Animation_2D>()->duration = 0.1f;

    
    auto tf = anim.get_ref<Transform>();
    auto a_im = anim.get_ref<Animation_2D>()->size;
   
    physics->physics_body_create({tf->position.x, tf->position.y},{1.0f,1.0f},{0.0f,0.0f},1,1,false,hit_sprite,nullptr,0);
    tf->body_id = 0;
    auto plat = handler->create_UI_image("UI 2");
    plat.get_ref<Transform>()->position = Vector3D(100.0f,100.0f,0.0f);
    plat.get_ref<Image>()->image = resource_manager->create_resource_from_file<Texture>(L"../../src/Assets/Textures/brick_d.jpg");
    plat.get_ref<Image>()->size = {150,50,0,0};
    auto ptf = plat.get_ref<Transform>();
    a_im = plat.get_ref<Animation_2D>()->size;

    physics->physics_static_body_create({ptf->position.x,ptf->position.y},{3.0f,1.0f},1);
    //input->lock_cursor(true);


    //physics->physics_body_create()

    lua_State* L = luaL_newstate();
    luaL_dostring(L,"x = 42");
    lua_getglobal(L,"x");
    lua_Number num = lua_tonumber(L,1);
    std::cout<<num<<" :LUA number.\n";
    lua_close(L);
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

    auto delta_time = (float)elapsed_time.count(); //measured in seconds
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
    rot += delta_time;
    player.get_ref<Transform>()->rotation = Vector3D(0.0f,sin(rot),0.0f);
    player.get_ref<Transform>()->compute_world_matrix();
    rot_y += d_pos.x * 0.001f;
    rot_x += d_pos.y * 0.001f;

    cam.get_ref<Transform>()->rotation = Vector3D(rot_x,rot_y,0.0f);
    cam.get_ref<Transform>()->position = cam_pos;
    cam.get_ref<Transform>()->compute_world_matrix();
   
    physics->physics_update(delta_time);
    for(auto sprite_entity : handler->get_sprites()) {
        sprite_entity.second.get_ref<Transform>()->position = physics->physics_body_get(sprite_entity.second.get_ref<Transform>()->body_id)->aabb.position;
    }
    graphics->update(delta_time);
   
}

void Game::quit() {
    is_running = false;
}