#include "app_window.h"
#include <iostream>

App_Window::App_Window()
{
}

App_Window::~App_Window()
{
}

void App_Window::on_create()
{
    Graphics_Engine::get_engine()->init();
    swapchain = Graphics_Engine::get_engine()->create_swap_chain();

    RECT rc = this->get_client_window_rect();
    UINT width = rc.right - rc.left;
    UINT height = rc.bottom - rc.top;
    swapchain->init(this->window_handle,width,height);

    Vertex vertices[] = {
        {-0.5f,-0.5f,0.0f,  1.0f,0.0f,0.0f},
        {0.0f,0.5f,0.0f,  0.0f,1.0f,0.0f},
        {0.5f,-0.5f,0.0f,  0.0f,0.0f,1.0f},

        {0.5f,0.5f,0.0f,  1.0f,0.0f,1.0f},
        {0.5f,-0.5f,0.0f,  1.0f,1.0f,0.0f},
        {-0.5f,-0.5f,0.0f,  0.0f,1.0f,1.0f}
    };

    vertex_buffer = Graphics_Engine::get_engine()->create_vertex_buffer();
    UINT num_vertices = ARRAYSIZE(vertices);

    void* shader_byte_code = nullptr;
    size_t shader_size = 0;
    Graphics_Engine::get_engine()->compile_vertex_shader(L"C:/Users/zachm/OneDrive/Desktop/Moryx_engine/src/shaders/vertex.hlsl","main",&shader_byte_code,&shader_size);
     
    vertex_shader = Graphics_Engine::get_engine()->create_vertex_shader(shader_byte_code,shader_size);
    
    vertex_buffer->load(vertices,sizeof(Vertex),num_vertices,shader_byte_code,shader_size);

    Graphics_Engine::get_engine()->release_compiled_shader();

    Graphics_Engine::get_engine()->compile_pixel_shader(L"C:/Users/zachm/OneDrive/Desktop/Moryx_engine/src/shaders/fragment.hlsl", "main", &shader_byte_code, &shader_size);
    pixel_shader = Graphics_Engine::get_engine()->create_pixel_shader(shader_byte_code,shader_size);

    Graphics_Engine::get_engine()->release_compiled_shader();
     
}

void App_Window::on_update() {

    Graphics_Engine::get_engine()->get_device_context()->clear_render_target_color(this->swapchain,0.0f,0.3f,0.4f,1.0f);
    

    RECT rc = this->get_client_window_rect();
    UINT width = rc.right - rc.left;
    UINT height = rc.bottom - rc.top;

    Graphics_Engine::get_engine()->get_device_context()->set_viewport_size(width,height);
    Graphics_Engine::get_engine()->get_device_context()->set_vertex_shader(vertex_shader);
    Graphics_Engine::get_engine()->get_device_context()->set_pixel_shader(pixel_shader);
    Graphics_Engine::get_engine()->get_device_context()->set_vertex_buffer(vertex_buffer);
    Graphics_Engine::get_engine()->get_device_context()->draw_triangle_list(vertex_buffer->get_num_vertices(),0);
  
    swapchain->present(true);
}

void App_Window::on_destroy() {
    Window::on_destroy();
    swapchain->release();
    vertex_buffer->release();
    vertex_shader->release();
    pixel_shader->release();
    Graphics_Engine::get_engine()->release();
}
