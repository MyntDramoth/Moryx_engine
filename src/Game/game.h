#pragma once

#include "display.h"

#include "../Input_System/input_system.h"
#include "../Graphics_System/prerequisites.h"
#include "../Graphics_System/Windowing/window.h"
#include "../Graphics_System/Graphics/graphics_engine.h"
#include "../Graphics_System/Resource/resource_manager.h"
#include "../Graphics_System/Resource/resource.h"
#include "../Graphics_System/Resource/mesh.h"
#include "../Graphics_System/Resource/texture.h"
#include "../Graphics_System/Resource/material.h"

class Game
{
public:
    Game();
    virtual ~Game();

    void run();
    void quit();

    Graphics_Engine* get_graphics_engine() { return graphics.get();}

protected:
    virtual void on_create() {};
    virtual void on_update(float delta_time) {};
    virtual void on_quit() {};

   

private:
    void on_display_size_change(const Rect& size);
    void on_update_internal();

    std::unique_ptr<Input_System> input;
    std::unique_ptr<Graphics_Engine> graphics;
    std::unique_ptr<Display> display;
    std::unique_ptr<Resource_Manager> resource_manager;
    bool is_running = true;

    //------------------------
    // TEMP RESOURCE STORAGE
    //------------------------

    mesh_sptr mesh;
    material_sptr material;

    friend class Graphics_Engine;
    friend class Display;
};