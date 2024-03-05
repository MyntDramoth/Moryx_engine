#include "input_system.h"

#include <Windows.h>

Input_System* Input_System::system = nullptr;

Input_System::Input_System() {

}

Input_System::~Input_System() {
    Input_System::system = nullptr;
}

void Input_System::update() {

    POINT current_mouse_pos = {};
    GetCursorPos(&current_mouse_pos);

    if(is_first_time) {
        old_mouse_pos = Point(current_mouse_pos.x,current_mouse_pos.y);
        is_first_time = false;
    }

    if(current_mouse_pos.x != old_mouse_pos.x || current_mouse_pos.y != old_mouse_pos.y) {
        //MOUSE MOVED EVENT
        std::map<Input_Listener*,Input_Listener*>::iterator iterator = map_listeners.begin();
        while(iterator != map_listeners.end()) {
            iterator->second->on_mouse_move(Point(current_mouse_pos.x, current_mouse_pos.y));
            ++iterator;
        }
    }
    old_mouse_pos = Point(current_mouse_pos.x,current_mouse_pos.y);

    if(GetKeyboardState(key_state)) {
        for(unsigned int i = 0; i < 255;i++) {
            // KEY IS DOWN
            if(key_state[i] & 0x80) {
                std::map<Input_Listener*,Input_Listener*>::iterator iterator = map_listeners.begin();
                while(iterator != map_listeners.end()) {

                    if(i == VK_LBUTTON) {
                        if(key_state[i] != old_key_state[i]) {
                            iterator->second->on_left_mouse_down(Point(current_mouse_pos.x,current_mouse_pos.y));
                        }
                    }
                    else if(i == VK_RBUTTON) {
                        if(key_state[i] != old_key_state[i]) {
                            iterator->second->on_right_mouse_down(Point(current_mouse_pos.x,current_mouse_pos.y));
                        }
                    }
                    else {
                        iterator->second->on_key_down(i);
                    }
                    ++iterator;
                }
            // KEY IS UP
            } else {  

                if(key_state[i] != old_key_state[i]) {
                    std::map<Input_Listener*,Input_Listener*>::iterator iterator = map_listeners.begin();
                    while(iterator != map_listeners.end()) {
                        if(i == VK_LBUTTON) {
                            iterator->second->on_left_mouse_up(Point(current_mouse_pos.x,current_mouse_pos.y));
                        }
                        else if(i == VK_RBUTTON) {
                            iterator->second->on_right_mouse_up(Point(current_mouse_pos.x,current_mouse_pos.y));
                        }
                        else {
                            iterator->second->on_key_up(i);
                        }
                        ++iterator;
                    }
                }
            }
        }
    }
    //store current key state
    memcpy(old_key_state,key_state,sizeof(unsigned char) * 256);
}

void Input_System::add_listener(Input_Listener *listener)
{
    map_listeners.insert(std::make_pair<Input_Listener*,Input_Listener*> (
        std::forward<Input_Listener*>(listener),std::forward<Input_Listener*>(listener)
        ));
}

void Input_System::remove_listener(Input_Listener *listener) {
    std::map<Input_Listener*,Input_Listener*>::iterator iterator = map_listeners.find(listener);
    if(iterator != map_listeners.end()) {
        map_listeners.erase(iterator);
    }
}

void Input_System::set_cursor_pos(const Point &pos) {
    SetCursorPos(pos.x,pos.y);
}

void Input_System::show_cursor(bool show) {
    ShowCursor(show);
}

void Input_System::create() {
    if(Input_System::system) {throw std::exception("input system already exists!");}
    Input_System::system = new Input_System();
}

void Input_System::release() {
    if(!Input_System::system) {return;}
    delete Input_System::system;
}

Input_System *Input_System::get_input_system() {
    return system;
}
