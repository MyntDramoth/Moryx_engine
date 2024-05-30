#pragma once


#include "../Math/rect.h"


class Window {
public:
    Window();
    virtual ~Window();

    //EVENTS

    virtual void on_create();
    virtual void on_update();
    virtual void on_destroy();

    virtual void on_focus();
    virtual void on_kill_focus();
    virtual void on_resize(const Rect& size);

    Rect get_screen_size();
    Rect get_client_size();

protected:
    void* window_handle;
    //Rect size = {1920,1080,0,0};
    Rect size = {1024,768,0,0};
};