#pragma once
#include <chrono>

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
#include "entity_handler.h"

class Game
{
public:
    Game();
    virtual ~Game();

    void run();
    void quit();

    Graphics_Engine* get_graphics_engine() { return graphics.get();}
    entity_handler* get_entity_handler() {return handler.get();}

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
    std::unique_ptr<entity_handler> handler;
    bool is_running = true;


    std::chrono::system_clock::time_point previous_time;

    //------------------------
    // TEMP RESOURCE STORAGE
    //------------------------

    mesh_sptr mesh;
    material_sptr material;

    flecs::entity player;

    friend class Graphics_Engine;
    friend class Display;
};