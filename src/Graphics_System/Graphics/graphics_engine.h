#pragma once

#include "../prerequisites.h"
#include "../Math/matrix4x4.h"
#include "Render_System/render_system.h"



class Graphics_Engine {
public:
    Graphics_Engine(Game* game);
    ~Graphics_Engine();

   Render_System* get_render_system();
   

    void update(float delta_time);
    
private:

    std::unique_ptr<Render_System> render_system = nullptr;
    Game* game = nullptr;
};

