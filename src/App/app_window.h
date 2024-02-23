#pragma once

#include <Windows.h>
#include <chrono>

#include "../Engine/math/vector3D.h"
#include "../Engine/math/matrix4x4.h"


#include "../Engine/windowing/window.h"
#include "../Engine/graphics_engine/graphics_engine.h"
#include "../Engine/graphics_engine/swapchain/swapchain.h"
#include "../Engine/graphics_engine/device_context/device_context.h"
#include "../Engine/graphics_engine/vertex_buffer/vertex_buffer.h"
#include "../Engine/graphics_engine/constant_buffer/constant_buffer.h"
#include "../Engine/graphics_engine/index_buffer/index_buffer.h"
/*
struct Vec3 {
    float x,y,z;
};*/

struct Vertex {
    Vector3D position;
    Vector3D color;
};

__declspec(align(16))
struct Const_Buff {
    Matrix4x4 world_space;
    Matrix4x4 view_space;
    Matrix4x4 projection;
    unsigned int time;
};

class App_Window : public Window {
public:
    App_Window();
    ~App_Window();

    void update_constant_buffer();

    //Inherited via Window
    virtual void on_create() override;
    virtual void on_update() override;
    virtual void on_destroy() override;

private:
    std::chrono::high_resolution_clock::time_point current_time;
    float delta_time;
    std::chrono::high_resolution_clock::time_point new_time;
    

    float FPS;
    float d_pos = 0.01f;
    float d_scale = 0.01f;

    Swapchain* swapchain;
    Index_Buffer* index_buffer;
    Constant_Buffer* constant_buffer;
    Vertex_Buffer* vertex_buffer;
    Vertex_Shader* vertex_shader;
    Pixel_Shader* pixel_shader;
};