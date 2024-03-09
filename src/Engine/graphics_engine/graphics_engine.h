#pragma once

#include "prerequisites.h"

#include "render_system/render_system.h"
#include "resource_manager/texture_manager/texture_manager.h"


class Graphics_Engine {
public:
    
    Render_System* get_render_system();
    Texture_Manager* get_texture_manager();
    static Graphics_Engine* get_engine();
    static void create();
    static void release();
    
    //default simple shaders
    
private:
    //these are private because the class is a singleton
    Graphics_Engine();
    ~Graphics_Engine();
    Render_System* render_system = nullptr;
    Texture_Manager* texture_manager = nullptr;
    static Graphics_Engine* engine;
    
};