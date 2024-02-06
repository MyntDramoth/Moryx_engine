#pragma once

#include "../Engine/windowing/window.h"
#include "../Engine/graphics_engine/graphics_engine.h"
#include "../Engine/graphics_engine/swapchain/swapchain.h"
#include "../Engine/graphics_engine/device_context/device_context.h"
#include "../Engine/graphics_engine/vertex_buffer/vertex_buffer.h"

struct Vec3 {
    float x,y,z;
};

struct Vertex {
    Vec3 position;

};

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
    Vertex_Buffer* vertex_buffer;
};