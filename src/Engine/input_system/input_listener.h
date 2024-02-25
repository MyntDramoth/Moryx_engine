#pragma once

#include "../math/point.h"

class Input_Listener {
public:
    Input_Listener() {

    };

    ~Input_Listener() {

    };

    //KEYBOARD - Pure Virtual Callback Functions
    virtual void on_key_down(int key) = 0;
    virtual void on_key_up(int key) = 0;

     //MOUSE - Pure Virtual Callback Functions
    virtual void on_mouse_move(const Point &delta_mouse_pos) = 0;
    virtual void on_left_mouse_down(const Point &mouse_pos) = 0;
    virtual void on_left_mouse_up(const Point &mouse_pos) = 0;
    virtual void on_right_mouse_down(const Point &mouse_pos) = 0;
    virtual void on_right_mouse_up(const Point &mouse_pos) = 0;
};