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
    //update_camera();
    update_third_person_camera();
    update_light(); 
    update_skybox();

}

void App_Window::render() {

    Graphics_Engine::get_engine()->get_render_system()->get_device_context()->clear_render_target_color(this->swapchain,0.0f,0.3f,0.4f,1.0f);
    

    RECT rc = this->get_client_window_rect();
    UINT width = rc.right - rc.left;
    UINT height = rc.bottom - rc.top;


    Graphics_Engine::get_engine()->get_render_system()->get_device_context()->set_viewport_size(width,height);
    
    
    
    
    e_mats.clear();
    e_mats.push_back(spaceship_material);

    update_model(Vector3D(0.0f,0.0f,0.0f),Vector3D(0.0f,0.0f,0.0f),Vector3D(1.0f,1.0f,1.0f),e_mats);

    draw_mesh(spaceship_mesh,e_mats);

    
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

    cam_rot.x += delta_mouse_cursor.y  * delta_time * 0.1f;
    cam_rot.y += delta_mouse_cursor.x  * delta_time * 0.1f;

    Matrix4x4 camera_matrix, temp;
    camera_matrix.set_identity();

    temp.set_identity();
    temp.set_rotation_x(cam_rot.x);
    camera_matrix *= temp;
    temp.set_identity();
    temp.set_rotation_y(cam_rot.y);
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

void App_Window::update_third_person_camera() {

    cam_rot.x += delta_mouse_cursor.y  * delta_time * 0.1f;
    cam_rot.y += delta_mouse_cursor.x  * delta_time * 0.1f;

    //stops camera from rotating past 90 degrees in the up and down direction. 
    //stops camera at the top and bottom of the model to prevent flipping the scene upside down

    if(cam_rot.x >= 1.57f) {
        cam_rot.x = 1.57f;
    }
    else if(cam_rot.x <= -1.57f) {
        cam_rot.x = -1.57f;
    }


    Matrix4x4 camera_matrix, temp;
    camera_matrix.set_identity();

    temp.set_identity();
    temp.set_rotation_x(cam_rot.x);
    camera_matrix *= temp;
    temp.set_identity();
    temp.set_rotation_y(cam_rot.y);
    camera_matrix *= temp;


    cam_pos = cam_focus_pos;


    Vector3D new_pos = cam_pos + camera_matrix.get_z_direction() * (-cam_dist_to_focus) + camera_matrix.get_x_direction() * (rightward * 0.3f);

    camera_matrix.set_translation(new_pos);

    world_camera = camera_matrix;

    camera_matrix.inverse(); //turns it into a view matrix

    cam_view = camera_matrix;
   

    int width = (this->get_client_window_rect().right - this->get_client_window_rect().left);
    int height = (this->get_client_window_rect().bottom - this->get_client_window_rect().top);

   
    cam_projection.set_perspective_FOV(1.57f,((float)width/(float)height),0.1f,100.0f);
}

void App_Window::update_model(Vector3D position, Vector3D rotation,Vector3D scale, const std::vector<material_sptr>& materials) {
    
    Const_Buff con;

    Matrix4x4 temp;
    
    con.time = time;
    con.world_space.set_identity();

    temp.set_identity();
    temp.set_scale(scale);
    con.world_space *= temp;

    temp.set_identity();
    temp.set_rotation_x(rotation.x);
    con.world_space *= temp;

    temp.set_identity();
    temp.set_rotation_y(rotation.y);
    con.world_space *= temp;

    temp.set_identity();
    temp.set_rotation_z(rotation.z);
    con.world_space *= temp;


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
    light_pos = Vector4D(180.0f,140.0f,70.0f,1.0f);

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

    //---------------------
    // SET BASE VALUES
    //---------------------
    is_camera_locked_to_mouse = true;

    Input_System::get_input_system()->add_listener(this);
    Input_System::get_input_system()->show_cursor(false);

    // ../../ is required due to the build directory containing the source directory/ files load based on source dir.

    TEXTURE_NOT_FOUND = Graphics_Engine::get_engine()->get_texture_manager()->create_texture_from_file(L"../../src/Assets/Textures/MISSING_TEXTURE.jpg");
   
    sky_tex = Graphics_Engine::get_engine()->get_texture_manager()->create_texture_from_file(L"../../src/Assets/Textures/stars_map.jpg");
    skybox_mesh = Graphics_Engine::get_engine()->get_mesh_manager()->create_mesh_from_file(L"../../src/Assets/Meshes/sphere.obj");
    
    
    default_material = Graphics_Engine::get_engine()->create_material(L"../../src/shaders/point_lights/vert_point_light.hlsl",L"../../src/shaders/point_lights/frag_point_light.hlsl");
    sky_material = Graphics_Engine::get_engine()->create_material(L"../../src/shaders/skybox_vert.hlsl",L"../../src/shaders/skybox_frag.hlsl");
    NO_TEXTURE_material = Graphics_Engine::get_engine()->create_material(default_material);

    RECT rc = this->get_client_window_rect();
    UINT width = rc.right - rc.left;
    UINT height = rc.bottom - rc.top;

    swapchain = Graphics_Engine::get_engine()->get_render_system()->create_swap_chain(this->window_handle, width, height);

    NO_TEXTURE_material->add_texture(TEXTURE_NOT_FOUND);
    NO_TEXTURE_material->set_culling_mode(BACK_CULLING);

    default_material->add_texture(TEXTURE_NOT_FOUND);
    default_material->set_culling_mode(BACK_CULLING);
   
    sky_material->set_culling_mode(FRONT_CULLING);
    sky_material->add_texture(sky_tex);

    current_time = std::chrono::high_resolution_clock::now();

    world_camera.set_translation(Vector3D(0.0f,0.0f,-2.0f));

    //---------------------
    // OBJECTS & MATERIALS
    //---------------------
   
    spaceship_mesh = Graphics_Engine::get_engine()->get_mesh_manager()->create_mesh_from_file(L"../../src/Assets/Meshes/spaceship.obj");
    spaceship_tex = Graphics_Engine::get_engine()->get_texture_manager()->create_texture_from_file(L"../../src/Assets/Textures/spaceship.jpg");
    spaceship_material = Graphics_Engine::get_engine()->create_material(default_material);
    spaceship_material->add_texture(spaceship_tex);
    spaceship_material->set_culling_mode(BACK_CULLING);

    e_mats.reserve(32);
}

void App_Window::on_update() {

    Input_System::get_input_system()->update();
    this->update();
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
   
    swapchain->resize_swapchain(rc.right - rc.left,rc.bottom - rc.top);
    this->render();
}

void App_Window::on_kill_focus() {
    Input_System::get_input_system()->remove_listener(this);
}

void App_Window::on_key_down(int key) {
    if(key == 'W') {
        forward = 1.0f;
    }
    if(key == 'A') {
        rightward = -1.0f;
    }
    if(key == 'S') {
        forward = -1.0f;
    }
    if(key == 'D') {
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

    RECT win_size = this->get_client_window_rect();
    int width = (win_size.right - win_size.left);
    int height = (win_size.bottom - win_size.top);

    delta_mouse_cursor = Vector2D(
    (mouse_pos.x - (win_size.left + (width/2.0f))),
    (mouse_pos.y - (win_size.top + (height/2.0f)))
    );

    Input_System::get_input_system()->set_cursor_pos(Point(win_size.left + (int)(width/2.0f),win_size.top + (int)(height/2.0f)));

}

void App_Window::on_left_mouse_down(const Point &mouse_pos) {
    
}

void App_Window::on_left_mouse_up(const Point &mouse_pos) {
     
}

void App_Window::on_right_mouse_down(const Point &mouse_pos) {
    
}

void App_Window::on_right_mouse_up(const Point &mouse_pos) {
     
}