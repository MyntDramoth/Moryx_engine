#include "display.h"



Display::Display() {
    auto rc = this->get_client_size();
    swapchain = Graphics_Engine::get_engine()->get_render_system()->create_swap_chain(static_cast<HWND>(this->window_handle),rc.width, rc.height);
}

Display::~Display() {

}