#pragma once

#include "input_listener.h"
#include "../math/point.h"

#include <map>

class Input_System {
public:
    Input_System();
    ~Input_System();

    void update();
    void add_listener(Input_Listener* listener);
    void remove_listener(Input_Listener* listener);

    static Input_System* get_input_system();

private:
    std::map<Input_Listener*,Input_Listener*> map_listeners;
    unsigned char key_state[256] = {};
    unsigned char old_key_state[256] = {};
    Point old_mouse_pos;
    bool is_first_time = true;
};