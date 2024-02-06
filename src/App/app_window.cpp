#include "app_window.h"

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
        {-0.5f,-0.5f,0.0f},
        {0.0f,0.5f,0.0f},
        {0.5f,-0.5f,0.0f}
    };

    vertex_buffer = Graphics_Engine::get_engine()->create_vertex_buffer();
    UINT num_vertices = ARRAYSIZE(vertices);

    Graphics_Engine::get_engine()->create_shaders();
   

    void* shader_byte_code = nullptr;
    UINT shader_size = 0;

     Graphics_Engine::get_engine()->get_shader_buffer_and_size(&shader_byte_code,&shader_size);

    vertex_buffer->load(vertices,sizeof(Vertex),num_vertices,shader_byte_code,shader_size);
}

void App_Window::on_update() {

    Graphics_Engine::get_engine()->get_device_context()->clear_render_target_color(this->swapchain,1,0,0,1);
    swapchain->present(true);

    RECT rc = this->get_client_window_rect();
    UINT width = rc.right - rc.left;
    UINT height = rc.bottom - rc.top;

    Graphics_Engine::get_engine()->get_device_context()->set_viewport_size(width,height);
    Graphics_Engine::get_engine()->set_shaders();
    Graphics_Engine::get_engine()->get_device_context()->set_vertex_buffer(vertex_buffer);
    Graphics_Engine::get_engine()->get_device_context()->draw_triangle_list(vertex_buffer->get_num_vertices(),0);


}

void App_Window::on_destroy() {
    Window::on_destroy();
    swapchain->release();
    vertex_buffer->release();
    Graphics_Engine::get_engine()->release();
}
