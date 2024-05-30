#include "display.h"
#include "game.h"
#include "../Graphics_System/Graphics/Render_System/Swapchain/swapchain.h"

Display::Display(Game* game):disp_game(game) {
    auto size = get_client_size();
    swapchain = game->get_graphics_engine()->get_render_system()->create_swap_chain(static_cast<HWND>(window_handle),size.width,size.height);
}

Display::~Display() {

}

void Display::on_resize(const Rect &size) {
    swapchain->resize_swapchain(size.width,size.height);
    disp_game->on_display_size_change(size);
}
