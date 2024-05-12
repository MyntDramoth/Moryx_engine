#pragma once

#include <Windows.h>
#include <chrono>

#include "../Engine/windowing/window.h"

//RENDERING ENGINE

#include "../Engine/graphics_engine/graphics_headers.h"

#include "../Engine/graphics_engine/graphics_engine.h"

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
    float light_radius = 500.0f;
    float time = 0.0f;
};

class App_Window : public Window, public Input_Listener {
public:
    App_Window();
    ~App_Window();

    void update();
    void render();
    void update_camera();
    void update_third_person_camera();
    void update_model(Vector3D position,Vector3D rotation,Vector3D scale, const std::vector<material_sptr>& materials);
    void update_skybox();
    void update_light();
    void draw_mesh(const mesh_sptr& mesh,const std::vector<material_sptr>& materials);
    void draw_gui(const font_sptr& Font, const char* text, Vector2D text_pos);

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
   
    float forward = 0.0f;
    float rightward = 0.0f;
    float time = 0.0f;
    
    //---------------------
    // CONST BUFFER STUFF
    //---------------------

    const_buffer_sptr constant_buffer {nullptr};

    Matrix4x4 world_camera;
    Matrix4x4 cam_view;
    Matrix4x4 cam_projection;
    Vector4D light_pos;
    Vector4D light_dir;

    Vector3D cam_rot;
    Vector3D cam_pos;
    Vector3D cam_focus_pos;

    Vector3D current_cam_rot;
    Vector3D current_cam_pos;
    Vector3D current_cam_focus_pos;
    float cam_dist_to_focus = 14.0f;
    Vector2D delta_mouse_cursor;

    float light_rot_y = 0.0f;

    //---------------------
    // REQUIRED TO FUNCTION
    //---------------------
    swapchain_sptr swapchain {nullptr};
    bool is_camera_locked_to_mouse = false;
    bool is_full_screen_mode = false;

    //---------------------
    // TIME STUFF
    //---------------------
    std::chrono::high_resolution_clock::time_point current_time;
    float delta_time;
    std::chrono::high_resolution_clock::time_point new_time;
    float FPS;

    //---------------------
    // USEFUL BITS
    //---------------------
    texture_sptr sky_tex {nullptr};
    mesh_sptr skybox_mesh {nullptr};
    material_sptr sky_material {nullptr};
    const_buffer_sptr sky_constant_buffer {nullptr};

    //---------------------
    // OBJECTS & MATERIALS
    //---------------------

    texture_sptr TEXTURE_NOT_FOUND {nullptr};
    

    mesh_sptr spaceship_mesh {nullptr};
    texture_sptr spaceship_tex {nullptr};
    texture_sptr spaceship_tex2 {nullptr};
    material_sptr spaceship_material {nullptr};

    texture_sptr d_stencil {nullptr};
    texture_sptr r_target {nullptr};


    material_sptr default_material {nullptr};
    material_sptr NO_TEXTURE_material {nullptr};

    mesh_sptr quad_mesh {nullptr};
    material_sptr quad_mat {nullptr};
    texture_sptr render_target = {nullptr};
    texture_sptr depth_stencil = {nullptr};

    font_sptr font = {nullptr};
    //Font_Utility font_util;

    Mesh_Data m_data;

    std::vector<material_sptr> e_mats;
};