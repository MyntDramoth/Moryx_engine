#pragma once

#include "../Engine/windowing/window.h"
#include "../Engine/graphics_engine/graphics_engine.h"
#include "../Engine/graphics_engine/swapchain/swapchain.h"
#include "../Engine/graphics_engine/device_context/device_context.h"

class App_Window : public Window {
public:
    App_Window();
    ~App_Window();

    //Inherited via Window
    virtual void on_create() override;
    virtual void on_update() override;
    virtual void on_destroy() override;

private:
    Swapchain* swapchain;

};