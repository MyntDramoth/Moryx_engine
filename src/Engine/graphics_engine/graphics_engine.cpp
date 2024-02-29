#include "graphics_engine.h"



Graphics_Engine::Graphics_Engine()
{
}

Graphics_Engine::~Graphics_Engine()
{
}

bool Graphics_Engine::init()
{
    render_system = new Render_System();
    render_system->init();

    return true;
}

bool Graphics_Engine::release()
{
    render_system->release();
    delete render_system;
    return true;
}

Render_System *Graphics_Engine::get_render_system()
{
    return render_system;
}

Graphics_Engine *Graphics_Engine::get_engine()
{
    static Graphics_Engine engine;
    return &engine;
}
