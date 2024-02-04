#pragma once

#include "../graphics_engine.h"

class Swapchain {
public:
    Swapchain();
    ~Swapchain();
    bool init(HWND hwnd,UINT width, UINT height);
    bool release();
private:
    IDXGISwapChain* swapchain;
};