#include "graphics_engine.h"

#include <exception>

Graphics_Engine* Graphics_Engine::engine = nullptr;

Graphics_Engine::Graphics_Engine() {
    try {
        render_system = new Render_System();
    } catch(...){throw std::exception("Failed to create graphics engine!");}
}

Graphics_Engine::~Graphics_Engine() {
    delete render_system;
    Graphics_Engine::engine = nullptr;
}

Render_System *Graphics_Engine::get_render_system() {
    return render_system;
}

Graphics_Engine *Graphics_Engine::get_engine() {
    return engine;
}

void Graphics_Engine::create() {
    if(Graphics_Engine::engine) {throw std::exception("graphics engine already exists!");}
    Graphics_Engine::engine = new Graphics_Engine();
}

void Graphics_Engine::release() {
     if(!Graphics_Engine::engine) {return;}
     delete Graphics_Engine::engine;
}
