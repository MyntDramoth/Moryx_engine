#include "input_system.h"

#include <Windows.h>

Input_System::Input_System() {

}

Input_System::~Input_System() {

}

void Input_System::update() {
    if(GetKeyboardState(key_state)) {
        for(unsigned int i = 0; i < 255;i++) {
            // KEY IS DOWN
            if(key_state[i] & 0x80) {
                std::map<Input_Listener*,Input_Listener*>::iterator iterator = map_listeners.begin();
                while(iterator != map_listeners.end()) {
                    iterator->second->on_key_down(i);
                    ++iterator;
                }
            // KEY IS UP
            } else {  

                if(key_state[i] != old_key_state[i]) {
                    std::map<Input_Listener*,Input_Listener*>::iterator iterator = map_listeners.begin();
                    while(iterator != map_listeners.end()) {
                        iterator->second->on_key_up(i);
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

Input_System *Input_System::get_input_system() {
    static Input_System system;
    return &system;
}
