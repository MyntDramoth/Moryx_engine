#pragma once

#include "input_listener.h"
#include "../math/point.h"

#include <map>

class Input_System {
public:
   

    void update();
    void add_listener(Input_Listener* listener);
    void remove_listener(Input_Listener* listener);

    void set_cursor_pos(const Point &pos);
    void show_cursor(bool show);

    static void create();
    static void release();

    static Input_System* get_input_system();

private:
     Input_System();
    ~Input_System();

    std::map<Input_Listener*,Input_Listener*> map_listeners;
    short key_state[256] = {};
    short old_key_state[256] = {};
    Point old_mouse_pos;
    bool is_first_time = true;

     static Input_System* system;
};