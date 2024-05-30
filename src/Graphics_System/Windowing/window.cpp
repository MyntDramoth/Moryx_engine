#include "window.h"
#include <exception>
#include <Windows.h>
#include "../prerequisites.h"

LRESULT CALLBACK WndProc(HWND hwnd,UINT msg, WPARAM wparam, LPARAM lparam) {
    switch(msg) {
        case WM_CREATE:
        {
           
            break;
        }
        case WM_SETFOCUS:
        {
            //happens when the window gets focus

            Window* window = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
            if(window) {
                window->on_focus();
            }

            break;
        }
        case WM_KILLFOCUS:
        {
            //happens when the window loses focus

            Window* window = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);

            if(window) {window->on_kill_focus();}

            break;
        }
        case WM_SIZE:
        {
            Window* window = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);

            if(window) {window->on_resize(window->get_client_size());}

            break;
        }
        case WM_DESTROY:
        {
            //happens when the window is destroyed

            Window* window = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);

            if(window) {window->on_destroy();}

            //PostQuitMessage(0);
            break;
        }
        case WM_CLOSE:
        {
            PostQuitMessage(0);
            break;
        }
        default:
        {
            return DefWindowProc(hwnd,msg,wparam,lparam);
            break;
        }
    }

    return NULL;
    
}

Window::Window() {
    const char* window_name = "Moryx Engine";
    int width,height;
    width = 1024;
    height = 720;

    WNDCLASSEX window_class = {};
 
    window_class.cbSize = sizeof(WNDCLASSEX);
    window_class.lpszClassName = (LPCSTR)"Window_Class";
    window_class.lpfnWndProc = &WndProc;

    auto class_ID = RegisterClassEx(&window_class);
    if(!class_ID) {MORYX_ERROR("failed to create Window!");}
    
    RECT rc = {0,0,size.width,size.height};
    AdjustWindowRect(&rc,WS_OVERLAPPEDWINDOW,false);

    window_handle = CreateWindowEx(NULL,MAKEINTATOM(class_ID), (LPCSTR)"Moryx Engine",
    WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,
    rc.right - rc.left,rc.bottom - rc.top,NULL,NULL,NULL,NULL);


    if(!window_handle) {MORYX_ERROR("failed to create Window!");}

    auto win_hndl = static_cast<HWND>(window_handle);

    SetWindowLongPtr(win_hndl, GWLP_USERDATA, (LONG_PTR)this);

    ShowWindow(win_hndl,SW_SHOW);
    UpdateWindow(win_hndl);
}

/*
bool Window::broadcast()
{
    MSG msg;

    if(!this->is_initialized) {
         //happens when the window is created
        
        SetWindowLongPtr(window_handle, GWLP_USERDATA, (LONG_PTR)this);
        
        this->on_create();
        this->is_initialized = true;
    }

    while(::PeekMessage(&msg,NULL,0,0,PM_REMOVE) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    this->on_update();

    //prevents throttling the CPU
    Sleep(0);

    return true;
}*/


Window::~Window() {
    DestroyWindow(static_cast<HWND>(window_handle));
}

void Window::on_create() {

}

void Window::on_update() {

}

void Window::on_destroy() {
    
}

void Window::on_focus() {
}


void Window::on_kill_focus() {

}

void Window::on_resize(const Rect& size) {

}

Rect Window::get_screen_size() {
    RECT rc = {};
    auto win_hndl = static_cast<HWND>(window_handle);


    rc.right = GetSystemMetrics(SM_CXSCREEN);
    rc.bottom = GetSystemMetrics(SM_CYSCREEN);
    
    return {rc.right - rc.left,rc.bottom - rc.top,0,0};
}

Rect Window::get_client_size()
{
    RECT rc = {};
    auto win_hndl = static_cast<HWND>(window_handle);
    GetClientRect(win_hndl,&rc);
    ClientToScreen(win_hndl,(LPPOINT)&rc.left);
    ClientToScreen(win_hndl,(LPPOINT)&rc.right);

    return {rc.right - rc.left,rc.bottom - rc.top,0,0};
}
