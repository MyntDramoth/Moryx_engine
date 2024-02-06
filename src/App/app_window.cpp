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
}

void App_Window::on_update() {

    Graphics_Engine::get_engine()->get_device_context()->clear_render_target_color(this->swapchain,1,0,0,1);
    swapchain->present(true);
}

void App_Window::on_destroy() {
    Window::on_destroy();
    swapchain->release();
    Graphics_Engine::get_engine()->release();
}
