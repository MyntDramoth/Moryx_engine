#include "window.h"

Window::Window()
{
}
/*
LRESULT CALLBACK WndProc(HWND hwnd,UINT msg, WPARAM wparam, LPARAM lparam) {

}*/

bool Window::init()
{
    const char* window_name = "Moryx Engine";
    int width,height;
    width = 1024;
    height = 720;

    WNDCLASSEX window_class;
    window_class.cbClsExtra = NULL;
    window_class.cbSize = sizeof(WNDCLASSEX);
    window_class.cbWndExtra = NULL;
    window_class.hbrBackground = (HBRUSH)COLOR_WINDOW;
    window_class.hCursor = LoadCursor(NULL,IDC_ARROW);
    window_class.hIcon = LoadIcon(NULL,IDI_APPLICATION);
    window_class.hIconSm = LoadIcon(NULL,IDI_APPLICATION);
    window_class.hInstance = NULL;
    window_class.lpszClassName = (LPCSTR)"Window_Class";
    window_class.lpszMenuName = (LPCSTR)"";
    window_class.style = NULL;
    //window_class.lpfnWndProc = &WndProc;

    if(!::RegisterClassEx(&window_class)) {
        return false;
    }

    window = ::CreateWindowEx(WS_EX_OVERLAPPEDWINDOW,window_class.lpszClassName,(LPCSTR)window_name,WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,width,height,NULL,NULL,NULL,NULL);


    ::ShowWindow(window,SW_SHOW);
    ::UpdateWindow(window);

    if(!window) {return false;}

    return true;
}

bool Window::release()
{

    if(!::DestroyWindow(window)) {
        return false;
    }
    return true;
}

Window::~Window()
{
}
