#pragma once

#include "prerequisites.h"

#include "render_system/render_system.h"


class Graphics_Engine {
public:
    Graphics_Engine();
    ~Graphics_Engine();
    bool init();
    bool release();

    Render_System* get_render_system();
    static Graphics_Engine* get_engine();
    
    //default simple shaders
    
private:
   
    Render_System* render_system = nullptr;
    
};