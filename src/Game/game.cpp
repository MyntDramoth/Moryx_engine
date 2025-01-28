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

    std::vector<Vertex_Mesh> mesh_V = {
            Vertex_Mesh(Vector3D(0.0f,0.0f,1.0f), Vector2D(0.0f,1.0f), Vector3D(0.0f,0.0f,0.0f), Vector3D(0.0f,0.0f,0.0f), Vector3D(0.0f,0.0f,0.0f))
        , 
            Vertex_Mesh(Vector3D(1.0f,0.0f,1.0f), Vector2D(1.0f,1.0f), Vector3D(0.0f,0.0f,0.0f), Vector3D(0.0f,0.0f,0.0f), Vector3D(0.0f,0.0f,0.0f))
        ,
            Vertex_Mesh(Vector3D(0.0f,0.0f,0.0f), Vector2D(0.0f,0.0f), Vector3D(0.0f,0.0f,0.0f), Vector3D(0.0f,0.0f,0.0f), Vector3D(0.0f,0.0f,0.0f))
        ,
            Vertex_Mesh(Vector3D(1.0f,0.0f,0.0f), Vector2D(1.0f,0.0f), Vector3D(0.0f,0.0f,0.0f), Vector3D(0.0f,0.0f,0.0f), Vector3D(0.0f,0.0f,0.0f))
    };

   std::vector<UINT> indexes = {
        0,1,2,
        3,2,1};
  

    std::vector<Material_Slot> ssssslot = {{0,6,0}};
    Vector2D atlas = Vector2D(1/8.0f,1/8.0f);
    
    //offset in y spot = up to (L * W) / ((L * W)/2)?
    // for 8x8 its max 64/8

     

    for(float x = 0.0f; x < 100.0f;x++) {
        for(float y = 0.0f; y < 100.0f;y++) {
            inst_data.push_back({Vector3D(x,1.0f,y),atlas,Vector2D(1/8,1/8)});
        }
    }
    //inst_data[0] = Instance_Data(Vector3D(0.0f,0.0f,0.0f),Vector2D(0.0f,0.0f));

    auto tile_map_mesh = resource_manager->create_custom_mesh( mesh_V.data(),4, indexes.data(),6, inst_data.data(),inst_data.size(), ssssslot.data(),1);

    auto tile_material = resource_manager->create_resource_from_file<Material>(L"../../src/shaders/tilemap.hlsl");
    //auto tile_material = resource_manager->create_resource_from_file<Material>(L"../../src/shaders/inst_mesh_layout.hlsl");
    tile_material->add_texture(pallete);
    tile_material->set_culling_mode(CULL_MODE::FRONT_CULLING);
    auto tmap = handler->create_entity("tmap");
    tmap.add<Transform>();
    tmap.get_ref<Transform>()->scale = Vector3D(10.0f,0.0f,10.0f);
    tmap.get_ref<Transform>()->position = Vector3D(0.0f,10.0f,0.0f);
    //tmap.get_ref<Transform>()->rotation = Vector3D::quaternion_to_euler(180.0f,0.0f,0.0f);
    tmap.get_ref<Transform>()->compute_world_matrix();
    handler->register_instance_mesh(tmap);
    tmap.get_ref<M_Mesh>()->mesh = tile_map_mesh;
    tmap.get_ref<M_Mesh>()->materials.push_back(tile_material);

    //std::cout << "inst buffer: " << tmap.get_ref<M_Mesh>()->mesh->get_inst_buff();

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
/*
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
    }*/

    {
        auto light = handler->create_light("light 1");
        light.get_ref<Transform>()->rotation = Vector3D(0.5f,0.5f,0.0f);
        light.get_ref<Transform>()->position = Vector3D(0.0f,10.0f,20.0f);
        light.get_ref<Transform>()->compute_world_matrix();

        light.get_ref<Light>()->color = Vector4D(1.0f,0.0f,0.0f,1.0f);

    }
    /*
    auto n = handler->create_entity("floor");
    n.add<Transform>();
    n.get_ref<Transform>()->compute_world_matrix();
    handler->register_mesh(n);
    n.get_ref<M_Mesh>()->mesh = terrain;
    n.get_ref<M_Mesh>()->materials.push_back(fmat);*/

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
    Vector2D atlas = Vector2D(1/8.0f,1/8.0f);
    auto fnSimplex = FastNoise::New<FastNoise::Simplex>();

    
    if(input->is_key_down(Key::G)){
        //inst_data = {};
        std::vector<Instance_Data> data2 = {};
        //MORYX_INFO("inst data size: " << inst_data.size());
        //for(int z = 0; z < 10;z++) {
            for(auto inst : inst_data) {
                // float var = fnSimplex->GenSingle3D(inst.pos.x,inst.pos.z,z + move,12121);
                //     //if(z == 0) {MORYX_INFO("noise val: " << var);}
                //     float overblock = fnSimplex->GenSingle3D(inst.pos.x,inst.pos.z,z + 1 + move,12121);
                //     float offset_y = inst.pos.z + (z*2);
                //     int offset_2D = (inst.pos.x + offset_y * 100);

                //     int X = inst.pos.x;
                //     int Y = inst.pos.z;
                //     if(var > 0.0f && offset_y < 100) {
                        
                //         if( overblock > 0.0f) {
                //             tile_data[X][Y][z] = 5;
                //             if(z!=0) {
                //                 data2.at((size_t)offset_2D).atlas_offset = Vector2D(5.0f/8.0f,5.0f/8.0f);
                //                 data2.at((size_t)offset_2D).pos.y = (float)z;
                //             }
                //             inst.atlas_offset = Vector2D(5.0f/8.0f,5.0f/8.0f);
                //             if(z == 10) {
                //                 tile_data[X][Y][z] = 400;
                //                 data2.at((size_t)offset_2D).atlas_offset = Vector2D(64.0f/8.0f,64.0f/8.0f);
                //                 data2.at((size_t)offset_2D).pos.y = (float)z;
                //             }
                //         } else {
                //             tile_data[X][Y][z] = 1;
                //             if(z!=0){
                //                 data2.at((size_t)offset_2D).atlas_offset = Vector2D(2.0f/8.0f,2.0f/8.0f);
                //                 data2.at((size_t)offset_2D).pos.y = (float)z;
                //             }
                //             inst.atlas_offset = Vector2D(2.0f/8.0f,2.0f/8.0f);
                //         }
                //     } else {
                //         tile_data[X][Y][z] = 0;
                //         if(z!=0){
                //             data2.at((size_t)(X + inst.pos.z * 100)).atlas_offset = Vector2D(1.0f/8.0f,1.0f/8.0f);
                //             data2.at((size_t)(X + inst.pos.z * 100)).pos.y = (float)z;
                //         }
                //         inst.atlas_offset = Vector2D(1.0f/8.0f,1.0f/8.0f);
                //     }
                //     inst.pos.y = (float)z;
                   
                //if(z == 0) {data2.push_back(inst);}
            
           // }
           data2.push_back(inst);
        }
        
       for(int z = 0; z < 10;z++) {
            for(int x = 0; x < 100;x++) {
                for (int y = 0; y < 100;y++) {
                
                   
                    float var = fnSimplex->GenSingle3D(y,x,z + move,12121);
                    //if(z == 0) {MORYX_INFO("noise val: " << var);}
                    float overblock = fnSimplex->GenSingle3D(y,x,z + 1 + move,12121);
                    float offset_y = y + (z*2);
                    int offset_2D = (x + offset_y * 100);
                    if(var > 0.0f && offset_y < 100) {
                        
                        if( overblock > 0.0f) {
                            tile_data[x][y][z] = 5;
                            data2.at((size_t)offset_2D).atlas_offset = Vector2D(5.0f/8.0f,5.0f/8.0f);
                            if(z == 10) {
                                tile_data[x][y][z] = 400;
                                data2.at((size_t)offset_2D).atlas_offset = Vector2D(64.0f/8.0f,64.0f/8.0f);
                                data2.at((size_t)offset_2D).pos.y = (float)z;
                            }
                        } else {
                            tile_data[x][y][z] = 1;
                            data2.at((size_t)offset_2D).atlas_offset = Vector2D(2.0f/8.0f,2.0f/8.0f);
                            data2.at((size_t)offset_2D).pos.y = (float)z;
                        }
                    } else {
                        tile_data[x][y][z] = 0;
                        data2.at((size_t)(x + y * 100)).atlas_offset = Vector2D(1.0f/8.0f,1.0f/8.0f);
                        data2.at((size_t)x + y * 100).pos.y = (float)z;
                    }
                }
            }
       }
       inst_data = {};
       inst_data = std::move(data2);

        move += delta_time;
    }

    int FPS = (1/delta_time);
    

    text.get_ref<Text>()->text = std::to_wstring(FPS);

    auto d_pos = input->get_delta_mouse_pos();
    //MORYX_INFO("Mouse X_pos: " << d_pos.x << " || Mouse Y_pos: "<< d_pos.y);
    rot += delta_time;
    // player.get_ref<Transform>()->rotation = Vector3D(0.0f,sin(rot),0.0f);
    // player.get_ref<Transform>()->compute_world_matrix();
    rot_y += d_pos.x * 0.001f;
    rot_x += d_pos.y * 0.001f;

    cam.get_ref<Transform>()->rotation = Vector3D(rot_x,rot_y,0.0f);
    cam.get_ref<Transform>()->position = cam_pos;
    //cam.get_ref<Transform>()->rotation = Vector3D::degrees_to_euler(-90.0f,180.0f,180.0f);
    //cam.get_ref<Transform>()->position = Vector3D(200.0f,cam_pos.y,200.0f);
    cam.get_ref<Transform>()->compute_world_matrix();
/*
    for(auto t : inst_data) {
        auto var = rand() % 64 + 1;
        t.atlas_offset = Vector2D((var/8),(var/8)); 
    }*/
   
    physics->physics_update(delta_time);
    for(auto sprite_entity : handler->get_sprites()) {
        sprite_entity.second.get_ref<Transform>()->position = physics->physics_body_get(sprite_entity.second.get_ref<Transform>()->body_id)->aabb.position;
    }
    graphics->update(delta_time);
   
}

void Game::quit() {
    is_running = false;
}