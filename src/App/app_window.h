#pragma once

#include "../Engine/windowing/window.h"
#include "../Engine/graphics_engine/graphics_engine.h"

class App_Window : public Window {
public:
    App_Window();
    ~App_Window();

    //Inherited via Window
    virtual void on_create() override;
    virtual void on_update() override;
    virtual void on_destroy() override;

};