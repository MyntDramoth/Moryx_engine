#pragma once

#include <Windows.h>

class Window {
public:
    Window();
    bool init();

    bool release();
    ~Window();

protected:
    HWND window;
};