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
    Const_Buff con;
    Matrix4x4 temp;

    con.world_space.set_identity();

    Matrix4x4 camera_matrix;
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

    con.view_space = camera_matrix;
   

    int width = (this->get_client_window_rect().right - this->get_client_window_rect().left);
    int height = (this->get_client_window_rect().bottom - this->get_client_window_rect().top);

   
    con.projection.set_perspective_FOV(1.57f,((float)width/(float)height),0.1f,100.0f);

    con.time = ::GetTickCount64();
    constant_buffer->update( Graphics_Engine::get_engine()->get_render_system()->get_device_context(), &con);


}

void App_Window::on_create() {

 

    Input_System::get_input_system()->add_listener(this);

    wood_tex = Graphics_Engine::get_engine()->get_texture_manager()->create_texture_from_file(L"C:/Users/zachm/OneDrive/Desktop/Moryx_engine/src/Assets/Textures/wood.jpg");
   
    if(wood_tex == nullptr) {throw std::exception("failed top load tex.");}

    RECT rc = this->get_client_window_rect();
    UINT width = rc.right - rc.left;
    UINT height = rc.bottom - rc.top;

    swapchain = Graphics_Engine::get_engine()->get_render_system()->create_swap_chain(this->window_handle, width, height);

   

    Vector3D vert_pos[] = {
        //front face
        {Vector3D(-0.5f,-0.5f,-0.5f)},
        {Vector3D(-0.5f, 0.5f,-0.5f)},
        {Vector3D( 0.5f, 0.5f,-0.5f)},
        {Vector3D( 0.5f,-0.5f,-0.5f)},
        //back face
        {Vector3D( 0.5f,-0.5f, 0.5f)},
        {Vector3D( 0.5f, 0.5f, 0.5f)},
        {Vector3D(-0.5f, 0.5f, 0.5f)},
        {Vector3D(-0.5f,-0.5f, 0.5f)}
    };

    Vector2D vert_uvs[] = {
         //front face
        {Vector2D(0.0f,0.0f)},
        {Vector2D(0.0f,1.0f)},
        {Vector2D(1.0f,0.0f)},
        {Vector2D(1.0f,1.0f)} 
    };

     Vertex vertices[] = {
        //Front Face
        {vert_pos[0],vert_uvs[1]},
        {vert_pos[1],vert_uvs[0]},
        {vert_pos[2],vert_uvs[2]},
        {vert_pos[3],vert_uvs[3]},
        //Back Face
        {vert_pos[4],vert_uvs[1]},
        {vert_pos[5],vert_uvs[0]},
        {vert_pos[6],vert_uvs[2]},
        {vert_pos[7],vert_uvs[3]},
         //Top Face
        {vert_pos[1],vert_uvs[1]},
        {vert_pos[6],vert_uvs[0]},
        {vert_pos[5],vert_uvs[2]},
        {vert_pos[2],vert_uvs[3]},
        //Bottom Face
        {vert_pos[7],vert_uvs[1]},
        {vert_pos[0],vert_uvs[0]},
        {vert_pos[3],vert_uvs[2]},
        {vert_pos[4],vert_uvs[3]},
        //Right Face
        {vert_pos[3],vert_uvs[1]},
        {vert_pos[2],vert_uvs[0]},
        {vert_pos[5],vert_uvs[2]},
        {vert_pos[4],vert_uvs[3]},
        //Left Face
        {vert_pos[7],vert_uvs[1]},
        {vert_pos[6],vert_uvs[0]},
        {vert_pos[1],vert_uvs[2]},
        {vert_pos[0],vert_uvs[3]}
        
    };
  
    UINT num_vertices = ARRAYSIZE(vertices);

    unsigned int indeces[] = {

        //FRONT
        0,1,2, //tri 1
        2,3,0, //tri 2
        //BACK
        4,5,6,
        6,7,4,
        //TOP
        8,9,10,
        10,11,8,
        //BOTTOM
        12,13,14,
        14,15,12,
        //RIGHT
        16,17,18,
        18,19,16,
        //LEFT
        20,21,22,
        22,23,20
    };

    UINT num_indeces = ARRAYSIZE(indeces);

    index_buffer = Graphics_Engine::get_engine()->get_render_system()->create_index_buffer(indeces, num_indeces);

    void* shader_byte_code = nullptr;
    size_t shader_size = 0;
    Graphics_Engine::get_engine()->get_render_system()->compile_vertex_shader(L"C:/Users/zachm/OneDrive/Desktop/Moryx_engine/src/shaders/vertex.hlsl","main",&shader_byte_code,&shader_size);
     
    vertex_shader = Graphics_Engine::get_engine()->get_render_system()->create_vertex_shader(shader_byte_code,shader_size);
    
    vertex_buffer = Graphics_Engine::get_engine()->get_render_system()->create_vertex_buffer(vertices, sizeof(Vertex), num_vertices, shader_byte_code, shader_size);

    Graphics_Engine::get_engine()->get_render_system()->release_compiled_shader();

    Graphics_Engine::get_engine()->get_render_system()->compile_pixel_shader(L"C:/Users/zachm/OneDrive/Desktop/Moryx_engine/src/shaders/fragment.hlsl", "main", &shader_byte_code, &shader_size);
    pixel_shader = Graphics_Engine::get_engine()->get_render_system()->create_pixel_shader(shader_byte_code,shader_size);

    Graphics_Engine::get_engine()->get_render_system()->release_compiled_shader();

    Const_Buff con;

    con.time = 0;
    constant_buffer = Graphics_Engine::get_engine()->get_render_system()->create_constant_buffer(&con, sizeof(Const_Buff));
    current_time = std::chrono::high_resolution_clock::now();

    world_camera.set_translation(Vector3D(0.0f,0.0f,-2.0f));
    Input_System::get_input_system()->show_cursor(false);
}

void App_Window::on_update() {
    
    Input_System::get_input_system()->update();
    

    

    Graphics_Engine::get_engine()->get_render_system()->get_device_context()->clear_render_target_color(this->swapchain,0.0f,0.3f,0.4f,1.0f);
    

    RECT rc = this->get_client_window_rect();
    UINT width = rc.right - rc.left;
    UINT height = rc.bottom - rc.top;


    Graphics_Engine::get_engine()->get_render_system()->get_device_context()->set_viewport_size(width,height);
    
    update();

    Graphics_Engine::get_engine()->get_render_system()->get_device_context()->set_constant_buffer(vertex_shader, constant_buffer);
    Graphics_Engine::get_engine()->get_render_system()->get_device_context()->set_constant_buffer(pixel_shader, constant_buffer);
    
    Graphics_Engine::get_engine()->get_render_system()->get_device_context()->set_vertex_shader(vertex_shader);
    Graphics_Engine::get_engine()->get_render_system()->get_device_context()->set_pixel_shader(pixel_shader);

    Graphics_Engine::get_engine()->get_render_system()->get_device_context()->set_texture(pixel_shader,wood_tex);
    
    Graphics_Engine::get_engine()->get_render_system()->get_device_context()->set_vertex_buffer(vertex_buffer);
    Graphics_Engine::get_engine()->get_render_system()->get_device_context()->set_index_buffer(index_buffer);

    Graphics_Engine::get_engine()->get_render_system()->get_device_context()->draw_indexed_triangle_list(index_buffer->get_size_index_list(),0,0);
    //Graphics_Engine::get_engine()->get_render_system()->get_device_context()->draw_triangle_list(vertex_buffer->get_num_vertices(),0);
  
    swapchain->present(true);

   

    new_time = std::chrono::high_resolution_clock::now();

    float frame_time = std::chrono::duration<float, std::milli>(new_time - current_time).count();
    
    current_time = new_time;
    
    delta_time = (float)frame_time / 1000.0f;
    
    FPS = (float)frame_time * 1000.0f;
    //std::cout<<(float)FPS<<std::endl;

}

void App_Window::on_destroy() {
    Window::on_destroy();
}

void App_Window::on_focus() {
    Input_System::get_input_system()->add_listener(this);
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
}

void App_Window::on_key_up(int key) {
    forward = 0.0f;
    rightward = 0.0f;
}

void App_Window::on_mouse_move(const Point &mouse_pos) {

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