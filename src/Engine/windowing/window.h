#pragma once

#include <Windows.h>

class Window {
public:
    Window();
    bool init();
    bool broadcast();
    bool release();
    bool is_running();
    ~Window();

    //EVENTS

    virtual void on_create() = 0;
    virtual void on_update() = 0;
    virtual void on_destroy();

    RECT get_client_window_rect();
    void set_HWND(HWND hwnd);

protected:
    HWND window_handle;
    bool m_is_running;
};