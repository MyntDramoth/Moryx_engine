#pragma once

#include <Windows.h>
#include <chrono>

#include "../Engine/math/vector3D.h"
#include "../Engine/math/vector2D.h"
#include "../Engine/math/matrix4x4.h"


#include "../Engine/windowing/window.h"

//RENDERING ENGINE

#include "../Engine/graphics_engine/prerequisites.h"

#include "../Engine/graphics_engine/graphics_engine.h"
#include "../Engine/graphics_engine/swapchain/swapchain.h"
#include "../Engine/graphics_engine/device_context/device_context.h"
#include "../Engine/graphics_engine/vertex_buffer/vertex_buffer.h"
#include "../Engine/graphics_engine/constant_buffer/constant_buffer.h"
#include "../Engine/graphics_engine/index_buffer/index_buffer.h"
#include "../Engine/graphics_engine/vertex_shader/vertex_shader.h"
#include "../Engine/graphics_engine/pixel_shader/pixel_shader.h"

#include "../Engine/graphics_engine/resource_manager/mesh_manager/mesh.h"

//INPUT SYSTEM
#include "../Engine/input_system/input_listener.h"

#include "../Engine/input_system/input_system.h"





struct Vertex {
    Vector3D position;
    Vector2D uv;
};

__declspec(align(16))
struct Const_Buff {
    Matrix4x4 world_space;
    Matrix4x4 view_space;
    Matrix4x4 projection;
    Vector4D light_dir;
    Vector4D cam_pos;
    Vector4D light_pos = Vector4D(0.0f,1.0f,0.0f,0.0f);
    float light_radius = 2.0f;
    float time = 0.0f;
};

class App_Window : public Window, public Input_Listener {
public:
    App_Window();
    ~App_Window();

    void update();
    void render();
    void update_camera();
    void update_model(Vector3D position, const material_sptr& material);
    void update_skybox();
    void update_light();
    void draw_mesh(const mesh_sptr& mesh,const material_sptr& material);

    //Inherited via Window
    virtual void on_create() override;
    virtual void on_update() override;
    virtual void on_destroy() override;
    virtual void on_focus() override;
    virtual void on_resize() override;
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
    

    bool is_camera_locked_to_mouse = false;
    bool is_full_screen_mode = false;

    float FPS;
    float d_pos = 0.01f;
    float d_scale = 0.01f;

    float rot_x = 0.0f;
    float rot_y = 0.0f;
    float light_rot_y = 0.0f;

    Matrix4x4 world_camera;
    float forward = 0.0f;
    float rightward = 0.0f;

    float time = 0.0f;

    swapchain_sptr swapchain {nullptr};
    index_buffer_sptr index_buffer {nullptr};
    const_buffer_sptr constant_buffer {nullptr};
    const_buffer_sptr sky_constant_buffer {nullptr};
    vert_buffer_sptr vertex_buffer {nullptr};
    vert_shader_sptr vertex_shader {nullptr};
    pix_shader_sptr pixel_shader {nullptr};

    pix_shader_sptr skybox_shader {nullptr};

    texture_sptr earth_tex {nullptr};
    texture_sptr brick_tex {nullptr};
    texture_sptr earth_spec_map {nullptr};
    texture_sptr clouds_tex {nullptr};
    mesh_sptr teapot_mesh {nullptr};
    material_sptr earth_material {nullptr};
    material_sptr bricks_material {nullptr};

    texture_sptr sky_tex {nullptr};
    mesh_sptr skybox_mesh {nullptr};
    material_sptr sky_material {nullptr};

    Matrix4x4 cam_view;
    Matrix4x4 cam_projection;
    Vector4D light_pos;
    Vector4D light_dir;
};