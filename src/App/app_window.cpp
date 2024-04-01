#include "app_window.h"

#include <iostream>

App_Window::App_Window()
{
}

App_Window::~App_Window()
{
}

void App_Window::update()
{
    update_camera();
    update_light();
   
    update_skybox();

}

void App_Window::render() {

    Graphics_Engine::get_engine()->get_render_system()->get_device_context()->clear_render_target_color(this->swapchain,0.0f,0.3f,0.4f,1.0f);
    

    RECT rc = this->get_client_window_rect();
    UINT width = rc.right - rc.left;
    UINT height = rc.bottom - rc.top;


    Graphics_Engine::get_engine()->get_render_system()->get_device_context()->set_viewport_size(width,height);
    
    update();
    
    
    e_mats.clear();
    e_mats.push_back(terrain_material);

    update_model(Vector3D(0.0f,0.0f,0.0f),e_mats);

    draw_mesh(terrain_mesh,e_mats);

    
    e_mats.clear();
    e_mats.push_back(barrel_material);
    e_mats.push_back(bricks_material);
    e_mats.push_back(window_material);
    e_mats.push_back(wood_material);

    update_model(Vector3D(0.0f,0.0f,0.0f),e_mats);

    draw_mesh(house_mesh,e_mats);
    //SKYBOX/SPHERE

    e_mats.clear();
    e_mats.push_back(sky_material);

    
    draw_mesh(skybox_mesh,e_mats);
  
    swapchain->present(true);

   

    new_time = std::chrono::high_resolution_clock::now();

    float frame_time = std::chrono::duration<float, std::milli>(new_time - current_time).count();
    
    current_time = new_time;
    
    delta_time = (float)frame_time / 1000.0f;
    
    FPS = (float)frame_time * 1000.0f;
    //std::cout<<(float)FPS<<std::endl;
    time += delta_time;

}

void App_Window::update_camera() {
    Matrix4x4 camera_matrix, temp;
    camera_matrix.set_identity();

    temp.set_identity();
    temp.set_rotation_x(rot_x);
    camera_matrix *= temp;
    temp.set_identity();
    temp.set_rotation_y(rot_y);
    camera_matrix *= temp;

    Vector3D new_pos = world_camera.get_translation() + camera_matrix.get_z_direction() * (forward * 0.3f) + camera_matrix.get_x_direction() * (rightward * 0.3f);

    camera_matrix.set_translation(new_pos);

    world_camera = camera_matrix;

    camera_matrix.inverse(); //turns it into a view matrix

    cam_view = camera_matrix;
   

    int width = (this->get_client_window_rect().right - this->get_client_window_rect().left);
    int height = (this->get_client_window_rect().bottom - this->get_client_window_rect().top);

   
    cam_projection.set_perspective_FOV(1.57f,((float)width/(float)height),0.1f,100.0f);

}

void App_Window::update_model(Vector3D position, const std::vector<material_sptr>& materials) {
    
    Const_Buff con;
    
    con.time = time;
    con.world_space.set_identity();
    con.world_space.set_translation(position);

    con.view_space = cam_view;
    con.projection = cam_projection;
    con.cam_pos = world_camera.get_translation();

    con.light_pos = light_pos;
    con.light_dir = light_dir;
    float dist_from_origin = 2.0f;
    //con.light_radius = light;

    for (size_t m = 0; m < materials.size();m++) {
        materials[m]->set_buffer_data(&con,sizeof(Const_Buff));
    }
}

void App_Window::update_skybox() {
   
    Const_Buff con;
    
    con.world_space.set_identity();

    con.world_space.set_scale(Vector3D(100.0f,100.0f,100.0f));

    con.world_space.set_translation(world_camera.get_translation());

    con.view_space = cam_view;
    con.projection = cam_projection;

    sky_material->set_buffer_data( &con,sizeof(Const_Buff));
}

void App_Window::update_light() {
   
    Matrix4x4 light_rot;
    //light_rot_y += sin(delta_time) * 0.7f;
    //light_rot_y -= delta_time;
    //light_rot.set_identity();
    //light_rot.set_rotation_y(light_rot_y);

    //float dist_from_origin = 2.0f;
    //light_rot_y += 0.02f;

    //light_pos = Vector4D(cos(light_rot_y) * dist_from_origin,1.0f,sin(light_rot_y) * dist_from_origin,0.0f);
    light_pos = Vector4D(180.0f,140.0f,70.0f,1.0f);

    //light_dir = light_rot.get_z_direction();
}

void App_Window::draw_mesh(const mesh_sptr &mesh, const std::vector<material_sptr>& materials) {

    Graphics_Engine::get_engine()->get_render_system()->get_device_context()->set_vertex_buffer(mesh->get_vert_buffer());
    Graphics_Engine::get_engine()->get_render_system()->get_device_context()->set_index_buffer(mesh->get_index_buffer());
    
    for (size_t m = 0; m < mesh->get_num_materials();m++) {
        if(m >= materials.size()) {break;}

        Material_Slot mat = mesh->get_material_slot((UINT)m);

        Graphics_Engine::get_engine()->set_material(materials[m]);

        Graphics_Engine::get_engine()->get_render_system()->get_device_context()->draw_indexed_triangle_list((UINT)mat.num_indeces,0,(UINT)mat.start_index);
    }
}

void App_Window::on_create() {

    is_camera_locked_to_mouse = true;

    Input_System::get_input_system()->add_listener(this);
    Input_System::get_input_system()->show_cursor(false);

    brick_tex = Graphics_Engine::get_engine()->get_texture_manager()->create_texture_from_file(L"C:/Users/zachm/OneDrive/Desktop/Moryx_engine/src/Assets/Textures/house_brick.jpg");
    sand_tex = Graphics_Engine::get_engine()->get_texture_manager()->create_texture_from_file(L"C:/Users/zachm/OneDrive/Desktop/Moryx_engine/src/Assets/Textures/sand.jpg");
    barrel_tex = Graphics_Engine::get_engine()->get_texture_manager()->create_texture_from_file(L"C:/Users/zachm/OneDrive/Desktop/Moryx_engine/src/Assets/Textures/barrel.jpg");
    window_tex = Graphics_Engine::get_engine()->get_texture_manager()->create_texture_from_file(L"C:/Users/zachm/OneDrive/Desktop/Moryx_engine/src/Assets/Textures/house_windows.jpg");
    wood_tex = Graphics_Engine::get_engine()->get_texture_manager()->create_texture_from_file(L"C:/Users/zachm/OneDrive/Desktop/Moryx_engine/src/Assets/Textures/house_wood.jpg");
 
    terrain_mesh = Graphics_Engine::get_engine()->get_mesh_manager()->create_mesh_from_file(L"C:/Users/zachm/OneDrive/Desktop/Moryx_engine/src/Assets/Meshes/terrain.obj");
    house_mesh = Graphics_Engine::get_engine()->get_mesh_manager()->create_mesh_from_file(L"C:/Users/zachm/OneDrive/Desktop/Moryx_engine/src/Assets/Meshes/house.obj");
   
    sky_tex = Graphics_Engine::get_engine()->get_texture_manager()->create_texture_from_file(L"C:/Users/zachm/OneDrive/Desktop/Moryx_engine/src/Assets/Textures/sky.jpg");
    skybox_mesh = Graphics_Engine::get_engine()->get_mesh_manager()->create_mesh_from_file(L"C:/Users/zachm/OneDrive/Desktop/Moryx_engine/src/Assets/Meshes/sphere.obj");
    
    RECT rc = this->get_client_window_rect();
    UINT width = rc.right - rc.left;
    UINT height = rc.bottom - rc.top;

    swapchain = Graphics_Engine::get_engine()->get_render_system()->create_swap_chain(this->window_handle, width, height);

    
    terrain_material = Graphics_Engine::get_engine()->create_material(L"C:/Users/zachm/OneDrive/Desktop/Moryx_engine/src/shaders/point_lights/vert_point_light.hlsl",L"C:/Users/zachm/OneDrive/Desktop/Moryx_engine/src/shaders/point_lights/frag_point_light.hlsl");
    bricks_material = Graphics_Engine::get_engine()->create_material(terrain_material);
    wood_material = Graphics_Engine::get_engine()->create_material(terrain_material);
    window_material = Graphics_Engine::get_engine()->create_material(terrain_material);
    barrel_material = Graphics_Engine::get_engine()->create_material(terrain_material);

    sky_material = Graphics_Engine::get_engine()->create_material(L"C:/Users/zachm/OneDrive/Desktop/Moryx_engine/src/shaders/point_lights/vert_point_light.hlsl",L"C:/Users/zachm/OneDrive/Desktop/Moryx_engine/src/shaders/skybox.hlsl");

    current_time = std::chrono::high_resolution_clock::now();

    world_camera.set_translation(Vector3D(0.0f,0.0f,-2.0f));
   
    terrain_material->add_texture(sand_tex);
    
    bricks_material->add_texture(brick_tex);
    wood_material->add_texture(wood_tex);
    window_material->add_texture(window_tex);
    barrel_material->add_texture(barrel_tex);

    terrain_material->set_culling_mode(BACK_CULLING);
    bricks_material->set_culling_mode(BACK_CULLING);
    wood_material->set_culling_mode(BACK_CULLING);
    window_material->set_culling_mode(BACK_CULLING);
    barrel_material->set_culling_mode(BACK_CULLING);

    sky_material->set_culling_mode(FRONT_CULLING);
    sky_material->add_texture(sky_tex);

    e_mats.reserve(32);
}

void App_Window::on_update() {

    Input_System::get_input_system()->update();
    this->render();
    
}

void App_Window::on_destroy() {
    Window::on_destroy();
    swapchain->set_fullsreen_state(false,1,1);
}

void App_Window::on_focus() {
    Input_System::get_input_system()->add_listener(this);
}

void App_Window::on_resize() {
    RECT rc = this->get_client_window_rect();
   
    swapchain->resize_swapchain(rc.right,rc.bottom);
    this->render();
}

void App_Window::on_kill_focus() {
    Input_System::get_input_system()->remove_listener(this);
}

void App_Window::on_key_down(int key) {
    if(key == 'W') {
        //rot_x += 0.7f * delta_time;
        forward = 1.0f;
    }
    if(key == 'A') {
        //rot_y += 0.7f * delta_time;
        rightward = -1.0f;
    }
    if(key == 'S') {
        //rot_x -= 0.7f * delta_time;
        forward = -1.0f;
    }
    if(key == 'D') {
        //rot_y -= 0.7f * delta_time;
        rightward = 1.0f;
    }
    if(key == VK_ESCAPE) {
        on_destroy();
    }
    if(key == 'K') {
        is_camera_locked_to_mouse = (is_camera_locked_to_mouse) ? false : true;
        Input_System::get_input_system()->show_cursor(!is_camera_locked_to_mouse);
    }
     if(key == 'F') {
        is_full_screen_mode = (is_full_screen_mode) ? false : true;
        RECT rc = this->get_screen_size();
        swapchain->set_fullsreen_state(is_full_screen_mode,rc.right,rc.bottom);
        
       
    }
}

void App_Window::on_key_up(int key) {
    forward = 0.0f;
    rightward = 0.0f;
}

void App_Window::on_mouse_move(const Point &mouse_pos) {

    if(!is_camera_locked_to_mouse) {return;}
    int width = (this->get_client_window_rect().right - this->get_client_window_rect().left);
    int height = (this->get_client_window_rect().bottom - this->get_client_window_rect().top);

    rot_x += (mouse_pos.y - (height/2.0f))  * delta_time * 0.1f;
    rot_y += (mouse_pos.x - (width/2.0f))  * delta_time * 0.1f;

    Input_System::get_input_system()->set_cursor_pos(Point(width/2.0f,height/2.0f));

}

void App_Window::on_left_mouse_down(const Point &mouse_pos) {
    
}

void App_Window::on_left_mouse_up(const Point &mouse_pos) {
     
}

void App_Window::on_right_mouse_down(const Point &mouse_pos) {
    
}

void App_Window::on_right_mouse_up(const Point &mouse_pos) {
     
}