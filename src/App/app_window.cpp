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
}

void App_Window::on_update() {

}

void App_Window::on_destroy() {
    Window::on_destroy();
    Graphics_Engine::get_engine()->release();
}
