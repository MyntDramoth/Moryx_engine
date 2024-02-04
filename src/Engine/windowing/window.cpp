#include "window.h"
#include <exception>

Window::Window()
{
}

LRESULT CALLBACK WndProc(HWND hwnd,UINT msg, WPARAM wparam, LPARAM lparam) {
    switch(msg) {
        case WM_CREATE:
        {
            //happens when the window is created
            Window* window = (Window*)((LPCREATESTRUCT)lparam)->lpCreateParams;

            // .. and then stored for later lookup

            SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)window);

            window->set_HWND(hwnd);
            window->on_create();

            break;
        }
        case WM_DESTROY:
        {
            //happens when the window is destroyed

            Window* window = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);

            window->on_destroy();

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
    window_class.lpfnWndProc = &WndProc;

    if(!::RegisterClassEx(&window_class)) {
        return false;
    }

    window_handle = ::CreateWindowEx(WS_EX_OVERLAPPEDWINDOW,window_class.lpszClassName,(LPCSTR)window_name,WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,width,height,NULL,NULL,NULL,this);


    ::ShowWindow(window_handle,SW_SHOW);
    ::UpdateWindow(window_handle);

    //if(!window_handle) {return false;}

    m_is_running = true;
    return true;
}

bool Window::broadcast()
{
    MSG msg;
    while(::PeekMessage(&msg,NULL,0,0,PM_REMOVE) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    this->on_update();

    //prevents throttling the CPU
    Sleep(0);

    return true;
}

bool Window::release()
{

    if(!::DestroyWindow(window_handle)) {
        return false;
    }
    return true;
}

bool Window::is_running()
{
    return m_is_running;
}

Window::~Window()
{
}

void Window::on_destroy()
{
    m_is_running = false;
}

RECT Window::get_client_window_rect()
{
    RECT rc;
    ::GetClientRect(this->window_handle,&rc);
    return rc;
}

void Window::set_HWND(HWND hwnd)
{
    this->window_handle = hwnd;
}
