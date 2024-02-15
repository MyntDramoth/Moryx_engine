#pragma once

#include <Windows.h>

#include "../Engine/windowing/window.h"
#include "../Engine/graphics_engine/graphics_engine.h"
#include "../Engine/graphics_engine/swapchain/swapchain.h"
#include "../Engine/graphics_engine/device_context/device_context.h"
#include "../Engine/graphics_engine/vertex_buffer/vertex_buffer.h"
#include "../Engine/graphics_engine/constant_buffer/constant_buffer.h"

struct Vec3 {
    float x,y,z;
};

struct Vertex {
    Vec3 position;
    Vec3 color;
};

__declspec(align(16))
struct Constant {
    unsigned int time;
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
    float current_time;

    Swapchain* swapchain;
    Constant_Buffer* constant_buffer;
    Vertex_Buffer* vertex_buffer;
    Vertex_Shader* vertex_shader;
    Pixel_Shader* pixel_shader;
};