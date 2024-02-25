#include "app_window.h"

#include "../Engine/input_system/input_system.h"

#include <iostream>

using namespace std::chrono_literals;

App_Window::App_Window()
{
}

App_Window::~App_Window()
{
}

void App_Window::update_constant_buffer()
{
    Const_Buff con;
    Matrix4x4 temp;
    
    d_pos += (delta_time / 2.0f);
    if(d_pos > 1.0f) {
        d_pos = 0.0f;
    }
    
    //con.world_space.set_translation(Vector3D::lerp(Vector3D(-2.0f,-2.0f,0.0f), Vector3D(2.0f,2.0f,0.0f), d_pos));
    //con.world_space.set_scale(Vector3D(1.0f,1.0f,0.0f));
    d_scale += (delta_time / 2.0f);
    /*
    con.world_space.set_scale(Vector3D::lerp(Vector3D(0.5f,0.5f,0.0f), Vector3D(2.0f,2.0f,0.0f), ((sin((float)d_scale)+1.0f) / 2.0f)));
    temp.set_translation(Vector3D::lerp(Vector3D(-2.0f,-2.0f,0.0f), Vector3D(2.0f,2.0f,0.0f), d_pos));
    
    con.world_space *= temp;*/

    con.world_space.set_scale(Vector3D(1.0f,1.0f,1.0f));

     temp.set_identity();
    temp.set_rotation_z(0.0f);

    con.world_space *= temp;

    temp.set_identity();
    temp.set_rotation_y(rot_y);

    con.world_space *= temp;

    temp.set_identity();
    temp.set_rotation_x(rot_x);

    con.world_space *= temp;

    con.view_space.set_identity();
    con.projection.set_orthogonal_matrix(
        (this->get_client_window_rect().right - this->get_client_window_rect().left)/400.0f,
        (this->get_client_window_rect().bottom - this->get_client_window_rect().top)/400.0f,
        -4.0f,
        4.0f
    );

    con.time = ::GetTickCount64();

    constant_buffer->update( Graphics_Engine::get_engine()->get_device_context(),&con);


}

void App_Window::on_create() {
    Input_System::get_input_system()->add_listener(this);

    Graphics_Engine::get_engine()->init();
    swapchain = Graphics_Engine::get_engine()->create_swap_chain();

    RECT rc = this->get_client_window_rect();
    UINT width = rc.right - rc.left;
    UINT height = rc.bottom - rc.top;
    swapchain->init(this->window_handle,width,height);

    Vertex vertices[] = {
        //front face
        {Vector3D(-0.5f,-0.5f,-0.5f),  Vector3D(1.0f,0.0f,0.0f)},
        {Vector3D(-0.5f, 0.5f,-0.5f),  Vector3D(0.0f,1.0f,0.0f)},
        {Vector3D( 0.5f, 0.5f,-0.5f),  Vector3D(0.0f,0.0f,1.0f)},
        {Vector3D( 0.5f,-0.5f,-0.5f),  Vector3D(1.0f,0.0f,1.0f)},
        //back face
        {Vector3D( 0.5f,-0.5f, 0.5f),  Vector3D(1.0f,1.0f,0.0f)},
        {Vector3D( 0.5f, 0.5f, 0.5f),  Vector3D(1.0f,1.0f,0.0f)},
        {Vector3D(-0.5f, 0.5f, 0.5f),  Vector3D(0.0f,1.0f,1.0f)},
        {Vector3D(-0.5f,-0.5f, 0.5f),  Vector3D(0.0f,1.0f,1.0f)}
    };

    vertex_buffer = Graphics_Engine::get_engine()->create_vertex_buffer();
    UINT num_vertices = ARRAYSIZE(vertices);

    unsigned int indeces[] = {

        //FRONT
        0,1,2, //tri 1
        2,3,0, //tri 2
        //BACK
        4,5,6,
        6,7,4,
        //TOP
        1,6,5,
        5,2,1,
        //BOTTOM
        7,0,3,
        3,4,7,
        //RIGHT
        3,2,5,
        5,4,3,
        //LEFT
        7,6,1,
        1,0,7
    };

    UINT num_indeces = ARRAYSIZE(indeces);

    index_buffer = Graphics_Engine::get_engine()->create_index_buffer();
    index_buffer->load(indeces,num_indeces);

    void* shader_byte_code = nullptr;
    size_t shader_size = 0;
    Graphics_Engine::get_engine()->compile_vertex_shader(L"C:/Users/zachm/OneDrive/Desktop/Moryx_engine/src/shaders/vertex.hlsl","main",&shader_byte_code,&shader_size);
     
    vertex_shader = Graphics_Engine::get_engine()->create_vertex_shader(shader_byte_code,shader_size);
    
    vertex_buffer->load(vertices,sizeof(Vertex),num_vertices,shader_byte_code,shader_size);

    Graphics_Engine::get_engine()->release_compiled_shader();

    Graphics_Engine::get_engine()->compile_pixel_shader(L"C:/Users/zachm/OneDrive/Desktop/Moryx_engine/src/shaders/fragment.hlsl", "main", &shader_byte_code, &shader_size);
    pixel_shader = Graphics_Engine::get_engine()->create_pixel_shader(shader_byte_code,shader_size);

    Graphics_Engine::get_engine()->release_compiled_shader();

    Const_Buff con;

    con.time = 0;
    constant_buffer = Graphics_Engine::get_engine()->create_constant_buffer();
    constant_buffer->load(&con,sizeof(Const_Buff));
    current_time = std::chrono::high_resolution_clock::now();
}

void App_Window::on_update() {
    Input_System::get_input_system()->update();
    

    update_constant_buffer();

    Graphics_Engine::get_engine()->get_device_context()->clear_render_target_color(this->swapchain,0.0f,0.3f,0.4f,1.0f);
    
    Graphics_Engine::get_engine()->get_device_context()->set_constant_buffer(vertex_shader, constant_buffer);
    Graphics_Engine::get_engine()->get_device_context()->set_constant_buffer(pixel_shader, constant_buffer);

    RECT rc = this->get_client_window_rect();
    UINT width = rc.right - rc.left;
    UINT height = rc.bottom - rc.top;

    Graphics_Engine::get_engine()->get_device_context()->set_viewport_size(width,height);
    Graphics_Engine::get_engine()->get_device_context()->set_vertex_shader(vertex_shader);
    Graphics_Engine::get_engine()->get_device_context()->set_pixel_shader(pixel_shader);

    
    Graphics_Engine::get_engine()->get_device_context()->set_vertex_buffer(vertex_buffer);
    Graphics_Engine::get_engine()->get_device_context()->set_index_buffer(index_buffer);

    Graphics_Engine::get_engine()->get_device_context()->draw_indexed_triangle_list(index_buffer->get_size_index_list(),0,0);
    //Graphics_Engine::get_engine()->get_device_context()->draw_triangle_list(vertex_buffer->get_num_vertices(),0);
  
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
    swapchain->release();
    constant_buffer->release();
    index_buffer->release();
    vertex_buffer->release();
    vertex_shader->release();
    pixel_shader->release();
    Graphics_Engine::get_engine()->release();
}

void App_Window::on_focus() {
    Input_System::get_input_system()->add_listener(this);
}

void App_Window::on_kill_focus() {
    Input_System::get_input_system()->remove_listener(this);
}

void App_Window::on_key_down(int key) {
    if(key == 'W') {
        rot_x += 0.7f * delta_time;
    }
    if(key == 'A') {
        rot_y += 0.7f * delta_time;
    }
    if(key == 'S') {
        rot_x -= 0.7f * delta_time;
    }
    if(key == 'D') {
        rot_y -= 0.7f * delta_time;
    }
}

void App_Window::on_key_up(int key) {

}

void App_Window::on_mouse_move(const Point &delta_mouse_pos) {
    rot_x -= delta_mouse_pos.y  * delta_time;
    rot_y -= delta_mouse_pos.x  * delta_time;

}

void App_Window::on_left_mouse_down(const Point &mouse_pos) {
    
}

void App_Window::on_left_mouse_up(const Point &mouse_pos) {
     
}

void App_Window::on_right_mouse_down(const Point &mouse_pos) {
    
}

void App_Window::on_right_mouse_up(const Point &mouse_pos) {
     
}
