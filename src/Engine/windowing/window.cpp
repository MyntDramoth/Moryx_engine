#include "window.h"
#include <exception>


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

            if(window) {window->on_resize();}

            break;
        }
        case WM_DESTROY:
        {
            //happens when the window is destroyed

            Window* window = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);

            if(window) {window->on_destroy();}

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
       throw std::exception("failed to create Window!");
    }

    window_handle = ::CreateWindowEx(WS_EX_OVERLAPPEDWINDOW,window_class.lpszClassName,(LPCSTR)window_name,WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,width,height,NULL,NULL,NULL,NULL);


    ::ShowWindow(window_handle,SW_SHOW);
    ::UpdateWindow(window_handle);

    //if(!window_handle) {return false;}

    m_is_running = true;
}


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
}

bool Window::is_running()
{
    if(m_is_running) {
        broadcast();
    }
    return m_is_running;
}

Window::~Window() {
    if(!::DestroyWindow(window_handle)) {
       
    }
   
}

void Window::on_destroy()
{
    m_is_running = false;
}

RECT Window::get_client_window_rect()
{
    RECT rc;
    ::GetClientRect(this->window_handle,&rc);
    ClientToScreen(this->window_handle,(LPPOINT)&rc.left);
    ClientToScreen(this->window_handle,(LPPOINT)&rc.right);
    return rc;
}

RECT Window::get_screen_size() {
    RECT rc;

    rc.right = GetSystemMetrics(SM_CXSCREEN);
    rc.bottom = GetSystemMetrics(SM_CYSCREEN);
    
    return rc;
}

Rect Window::get_client_size()
{
    RECT rec = this->get_client_window_rect();
    return Rect(rec.right - rec.left,rec.bottom - rec.top,rec.left,rec.top);
}
