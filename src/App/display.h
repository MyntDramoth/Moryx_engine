#pragma once

#include "../Engine/graphics_engine/prerequisites.h"
#include "../Engine/graphics_engine/graphics_engine.h"
#include "../Engine/windowing/window.h"
#include "../Engine/graphics_engine/swapchain/swapchain.h"
class Display: public Window
{
public:
    Display();
    ~Display();

private:
    swapchain_sptr swapchain;

    friend class Graphics_Engine;
};