#pragma once

#include <Windows.h>
#include <chrono>

#include "../Engine/math/vector3D.h"
#include "../Engine/math/matrix4x4.h"


#include "../Engine/windowing/window.h"

//RENDERING ENGINE
#include "../Engine/graphics_engine/graphics_engine.h"
#include "../Engine/graphics_engine/render_system/swapchain/swapchain.h"
#include "../Engine/graphics_engine/render_system/device_context/device_context.h"
#include "../Engine/graphics_engine/render_system/vertex_buffer/vertex_buffer.h"
#include "../Engine/graphics_engine/render_system/constant_buffer/constant_buffer.h"
#include "../Engine/graphics_engine/render_system/index_buffer/index_buffer.h"
#include "../Engine/graphics_engine/render_system/vertex_shader/vertex_shader.h"
#include "../Engine/graphics_engine/render_system/pixel_shader/pixel_shader.h"

//INPUT SYSTEM
#include "../Engine/input_system/input_listener.h"

#include "../Engine/input_system/input_system.h"




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

class App_Window : public Window, public Input_Listener {
public:
    App_Window();
    ~App_Window();

    void update();

    //Inherited via Window
    virtual void on_create() override;
    virtual void on_update() override;
    virtual void on_destroy() override;
    virtual void on_focus() override;
    virtual void on_kill_focus() override;

    //Inherited via Input_Listener
    virtual void on_key_down(int key) override;
    virtual void on_key_up(int key) override;

    virtual void on_mouse_move(const Point &mouse_pos) override;
    virtual void on_left_mouse_down(const Point &mouse_pos) override;
    virtual void on_left_mouse_up(const Point &mouse_pos) override;
    virtual void on_right_mouse_down(const Point &mouse_pos) override;
    virtual void on_right_mouse_up(const Point &mouse_pos) override;

private:
    std::chrono::high_resolution_clock::time_point current_time;
    float delta_time;
    std::chrono::high_resolution_clock::time_point new_time;
    

    float FPS;
    float d_pos = 0.01f;
    float d_scale = 0.01f;

    float rot_x = 0.0f;
    float rot_y = 0.0f;

    Matrix4x4 world_camera;
    float forward = 0.0f;
    float rightward = 0.0f;

    Swapchain* swapchain;
    Index_Buffer* index_buffer;
    Constant_Buffer* constant_buffer;
    Vertex_Buffer* vertex_buffer;
    Vertex_Shader* vertex_shader;
    Pixel_Shader* pixel_shader;
};