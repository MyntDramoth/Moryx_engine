#include "game.h"
#include "i_game_project_manager.h"
#include <io.h>

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
    auto pallete = resource_manager->create_resource_from_file<Texture>(L"../../Assets/painterly_atlas.png");

    Vector3D normal {0.0f,0.0f,0.0f};
    Vector3D binormal {0.0f,0.0f,0.0f};
    Vector3D tangent {0.0f,0.0f,0.0f};
    std::vector<Vertex_Mesh> mesh_V = {
               
        //              VERTEX_POSITION         |  VERTEX_UV         | NORMAL| BINORMAL| TANGENT
            Vertex_Mesh(Vector3D(0.0f,0.0f,1.0f), Vector2D(0.0f,1.0f), normal, binormal, tangent)
        , 
            Vertex_Mesh(Vector3D(1.0f,0.0f,1.0f), Vector2D(1.0f,1.0f), normal, binormal, tangent)
        ,
            Vertex_Mesh(Vector3D(0.0f,0.0f,0.0f), Vector2D(0.0f,0.0f), normal, binormal, tangent)
        ,
            Vertex_Mesh(Vector3D(1.0f,0.0f,0.0f), Vector2D(1.0f,0.0f), normal, binormal, tangent)
    };
    

   std::vector<UINT> indexes = {
        0,1,2,
        3,2,1};
  

    std::vector<Material_Slot> ssssslot = {{0,6,0}};

    atlas_size_y = 4.0f;
    atlas_size_x = 8.0f;
    Vector2D atlas = Vector2D((float)(1.0f/atlas_size_x),(float)(1.0f/atlas_size_y));
    float z = 0.0f;
    for(float x = 0.0f; x < 100.0f;x++) {
        for(float y = 0.0f; y < 100.0f;y++) {
            inst_data.push_back({Vector3D(x,z,y),atlas,Vector2D((float)((1.0f)/atlas_size_x),(float)(1.0f/atlas_size_y))});
            
        }
    }

    Vertex_Mesh* vert_list = mesh_V.data();
    UINT vert_list_size = 4;
    UINT* index_list  = indexes.data();
    UINT index_list_size = 6;
    Material_Slot* material_slot_data  = ssssslot.data();
    UINT num_mat_slots = 1;

    auto tile_map_mesh = resource_manager->create_custom_mesh( vert_list,vert_list_size, index_list,index_list_size, inst_data.data(),inst_data.size(), material_slot_data,num_mat_slots);

    auto tile_material = resource_manager->create_resource_from_file<Material>(L"../../src/shaders/tilemap.hlsl");
    tile_material->add_texture(pallete);
    tile_material->set_culling_mode(CULL_MODE::FRONT_CULLING);
    auto tmap = handler->create_entity("tmap");
    tmap.add<Transform>();
    tmap.get_ref<Transform>()->scale = Vector3D(10.0f,0.0f,10.0f);
    tmap.get_ref<Transform>()->position = Vector3D(0.0f,10.0f,0.0f);
    
    tmap.get_ref<Transform>()->compute_world_matrix();
    handler->register_instance_mesh(tmap);
    tmap.get_ref<M_Mesh>()->mesh = tile_map_mesh;
    auto var = resource_manager->create_resource_from_file<Texture>(L"../../Assets/painterly_atlas.png");
    tile_material->add_texture(var);
    tmap.get_ref<M_Mesh>()->materials.push_back(tile_material);

    

    //=====================//
    // TEMP RESOURCES      //
    //=====================//
    mesh = resource_manager->create_custom_mesh( mesh_V.data(),4, indexes.data(),6, ssssslot.data(),1);
    material = resource_manager->create_resource_from_file<Material>(L"../../src/shaders/mono_shader.hlsl");
    material->add_texture(pallete);

    {
        // auto light = handler->create_light("light 1");
        // light.get_ref<Transform>()->rotation = Vector3D(0.5f,0.5f,0.0f);
        // light.get_ref<Transform>()->position = Vector3D(0.0f,10.0f,20.0f);
        // light.get_ref<Transform>()->compute_world_matrix();

        // light.get_ref<Light>()->color = Vector4D(1.0f,0.0f,0.0f,1.0f);

    }
    

    input->set_lock_area(display->get_client_size());
   
    player = handler->create_entity("player");
    player.add<Transform>();
    player.get_ref<Transform>()->position = Vector3D(1.0f,0.0f,0.0f);
    player.get_ref<Transform>()->compute_world_matrix();

    handler->register_mesh(player);
    player.get_ref<M_Mesh>()->mesh = mesh;
    player.get_ref<M_Mesh>()->materials.push_back(material);
    

    cam = handler->create_camera("cam 1");
    cam.get_ref<Transform>()->position = Vector3D(0.0f,0.0f,-10.0f);
    cam.get_ref<Transform>()->rotation = Vector3D(0.0f,0.0f,0.0f);
    cam.get_ref<Transform>()->compute_world_matrix();
    cam.get_ref<Camera>()->far_plane = 2000;
    

    text = handler->create_text("text 1");
    text.get_ref<Transform>()->position = Vector3D(0.0f,0.0f,0.0f);
    text.get_ref<Text>()->text = L"Testing Text";
    text.get_ref<Text>()->font = resource_manager->create_resource_from_file<Font>(L"../../src/Assets/Fonts/Bahnschrift.font");

    lua_State* L = luaL_newstate();
    luaL_dostring(L,"x = 42");
    lua_getglobal(L,"x");
    lua_Number num = lua_tonumber(L,1);
    std::cout<<num<<" :LUA number.\n";
    lua_close(L);
    
    sound_sptr explode = resource_manager->create_resource_from_file<Sound>(L"../../Assets/breezys_mega_quest_stage_1.mp3");
   
    explode->play(1.0f);
}
    



Game::~Game() {

}

void Game::on_display_size_change(const Rect &size) {
    input->set_lock_area(display->get_client_size());
    on_update_internal();
}

void Game::on_update_internal()
{
    
    top_edge_uv = Vector2D(1.0f/atlas_size_x,1.0f/atlas_size_y);
    right_edge_uv = Vector2D(2.0f/atlas_size_x,1.0f/atlas_size_y);
    left_edge_uv = Vector2D(3.0f/atlas_size_x,1.0f/atlas_size_y);
    bottom_edge_uv = Vector2D(8.0f/atlas_size_x,1.0f/atlas_size_y);

    top_shadow_uv = {2.0f/atlas_size_x,2.0f/atlas_size_y};
    right_shadow_uv = {3.0f/atlas_size_x,2.0f/atlas_size_y};
    left_shadow_uv = {4.0f/atlas_size_x,2.0f/atlas_size_y};
    bottom_shadow_uv = {5.0f/atlas_size_x,2.0f/atlas_size_y};
    

    
    auto current_time = std::chrono::system_clock::now();
    auto elapsed_time = std::chrono::duration<double>();
    if(previous_time.time_since_epoch().count()) {
        elapsed_time = current_time - previous_time;  
    }
    previous_time = current_time;

    auto delta_time = (float)elapsed_time.count(); //measured in seconds
    input->update();
    handler->purge_entities(delta_time);
    float cam_speed = 100.0f;
    if(input->is_key_up(Key::ESCAPE)) {
        quit();
    }
    if(input->is_key_up(Key::ENTER)) {
       input->lock_cursor(true);
    }
    if(input->is_key_down(Key::W)) {
       
       cam_pos.z += delta_time * cam.get_ref<Transform>()->world_matrix.get_y_direction().z *cam_speed;
       cam_pos.x += delta_time * cam.get_ref<Transform>()->world_matrix.get_y_direction().x *cam_speed;
       cam_pos.y += delta_time * cam.get_ref<Transform>()->world_matrix.get_y_direction().y *cam_speed;
    }
    if(input->is_key_down(Key::S)) {
       cam_pos.z -= delta_time * cam.get_ref<Transform>()->world_matrix.get_y_direction().z *cam_speed;
       cam_pos.x -= delta_time * cam.get_ref<Transform>()->world_matrix.get_y_direction().x *cam_speed;
       cam_pos.y -= delta_time * cam.get_ref<Transform>()->world_matrix.get_y_direction().y *cam_speed;
    }
    if(input->is_key_down(Key::A)) {
       cam_pos.z -= delta_time * cam.get_ref<Transform>()->world_matrix.get_x_direction().z *cam_speed;
       cam_pos.x -= delta_time * cam.get_ref<Transform>()->world_matrix.get_x_direction().x *cam_speed;
       cam_pos.y -= delta_time * cam.get_ref<Transform>()->world_matrix.get_x_direction().y *cam_speed;
    }
    if(input->is_key_down(Key::D)) {
       cam_pos.z += delta_time * cam.get_ref<Transform>()->world_matrix.get_x_direction().z *cam_speed;
       cam_pos.x += delta_time * cam.get_ref<Transform>()->world_matrix.get_x_direction().x *cam_speed;
       cam_pos.y += delta_time * cam.get_ref<Transform>()->world_matrix.get_x_direction().y *cam_speed;
    }
    if(input->is_key_down(Key::SPACE)) {
       cam_pos.y += delta_time*cam_speed;
    }
    if(input->is_key_down(Key::SHIFT)) {
       cam_pos.y -= delta_time*cam_speed;
    }
    if(input->is_key_down(Key::F)) {
        MORYX_INFO("cam position: X:" << cam_pos.x << " || Y: "<<cam_pos.y<<" || Z:"<<cam_pos.z);
     }
    
    auto fnSimplex = FastNoise::New<FastNoise::Simplex>();
    auto SIMD_Simplex = FastSIMD::New<FastNoise::Perlin>();
    int move_speed = 5;
    if(input->is_key_down(Key::G)){
        if(!terrain_processing_done) {
            Start_terrain_thread(move,fnSimplex);
           
        }
         move.y += delta_time * move_speed;
    }
    
    if(input->is_key_down(Key::T)){
        if(!terrain_processing_done) {
            Start_terrain_thread(move,fnSimplex);
           
        }
         move.y -= delta_time * move_speed;
    }
    
    if(input->is_key_down(Key::J)){
        if(!terrain_processing_done) {
            Start_terrain_thread(move,fnSimplex);
           
        }
         move.x += delta_time * move_speed;
    }
    if(input->is_key_down(Key::H)){
        if(!terrain_processing_done) {
            Start_terrain_thread(move,fnSimplex);
           
        }
         move.x -= delta_time * move_speed;
    }

    if(input->is_key_down(Key::L)){
        if(!terrain_processing_done) {
            Start_terrain_thread(move,fnSimplex);
           
        }
         move.z += delta_time * move_speed;
    }
    if(input->is_key_down(Key::K)){
        if(!terrain_processing_done) {
            Start_terrain_thread(move,fnSimplex);
           
        }
         move.z -= delta_time * move_speed;
    }

    int FPS = (1/delta_time);
    
   
    text.get_ref<Text>()->text = std::to_wstring(FPS);

    auto d_pos = input->get_delta_mouse_pos();
    
    rot += delta_time;
    rot_y += d_pos.x * 0.001f;
    rot_x += d_pos.y * 0.001f;

   
    if(cam_pos.y < 64.0f) {cam_pos.y = 64.0f;}
    if(cam_pos.y > 280.0f) {cam_pos.y = 280.0f;}
    cam.get_ref<Transform>()->rotation = Vector3D::degrees_to_euler(-90.0f,180.0f,180.0f);
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

void work_thread(Vector3D mpos, Game* game, FastNoise::SmartNode<FastNoise::Simplex> i_simplex)
{
}
