#pragma once

#include "prerequisites.h"

#include "render_system/render_system.h"


class Graphics_Engine {
public:
    
    Render_System* get_render_system();
    static Graphics_Engine* get_engine();
    static void create();
    static void release();
    
    //default simple shaders
    
private:
    //these are private because the class is a singleton
    Graphics_Engine();
    ~Graphics_Engine();
    Render_System* render_system = nullptr;
    static Graphics_Engine* engine;
    
};