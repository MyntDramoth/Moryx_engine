#pragma once

#include <Windows.h>
#include "../math/rect.h"

class Window {
public:
    Window();
    
    bool is_running();
    ~Window();

    //EVENTS

    virtual void on_create() = 0;
    virtual void on_update() = 0;
    virtual void on_destroy();

    virtual void on_focus() = 0;
    virtual void on_kill_focus() = 0;
    virtual void on_resize() = 0;

    RECT get_client_window_rect();
    RECT get_screen_size();
    Rect get_client_size();

protected:
    HWND window_handle;
    bool m_is_running;
    bool is_initialized = false;
    bool broadcast();
};