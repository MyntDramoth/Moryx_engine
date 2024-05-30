#pragma once

#include "../Graphics_System/prerequisites.h"
#include "../Graphics_System/Windowing/window.h"

class Display: public Window
{
public:
    Display(Game* game);
    ~Display();

protected:
    virtual void on_resize(const Rect& size) override;

private:
    swapchain_sptr swapchain;
    Game* disp_game {nullptr};
    friend class Graphics_Engine;
};