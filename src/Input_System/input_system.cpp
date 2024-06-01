#include "input_system.h"

#include <Windows.h>


Input_System::Input_System() {

}

Input_System::~Input_System() {
   
}

void Input_System::update() {

    POINT current_mouse_pos = {};
    GetCursorPos(&current_mouse_pos);


    if(current_mouse_pos.x != old_mouse_pos.x || current_mouse_pos.y != old_mouse_pos.y) {
        //MOUSE MOVED EVENT
        delta_mouse_pos = Vector2D((float)current_mouse_pos.x - (float)old_mouse_pos.x, (float)current_mouse_pos.y - (float)old_mouse_pos.y);
    } else {
        delta_mouse_pos = Vector2D(0.0f,0.0f);
    }
    if(!is_cursor_locked) {
        old_mouse_pos = Vector2D(current_mouse_pos.x,current_mouse_pos.y);
    }
    else if (is_cursor_locked) {
        SetCursorPos((int)lock_area_center.x,(int)lock_area_center.y);
        old_mouse_pos = lock_area_center;
    }

    
    for(unsigned int i = 0; i < 255;i++) {

        key_state[i] = GetAsyncKeyState(i);
        // KEY IS DOWN
        if(key_state[i] & 0x8001) {
            final_key_state[i] = 0;
        // KEY IS UP
        } else {  

            if(key_state[i] != old_key_state[i]) {
                final_key_state[i] = 1;
            } else {
                final_key_state[i] = 2;
            }
        }
    }
    
    //store current key state
    memcpy(old_key_state,key_state,sizeof(short) * 256);
}

void Input_System::lock_cursor(bool lock) {
    is_cursor_locked = lock;
}

void Input_System::set_lock_area(const Rect &area) {
    lock_area = area;
    lock_area_center = Vector2D(area.left + (float)area.width /2.0f , area.top + (float)area.height /2.0f);
}

bool Input_System::is_key_down(const Key &key)
{
    short key_win = get_internal_key_code(key);
    return (final_key_state[key_win] == 0);
}

bool Input_System::is_key_up(const Key &key) {
    short key_win = get_internal_key_code(key);
    return (final_key_state[key_win] == 1);
}

Vector2D Input_System::get_delta_mouse_pos() {
    return delta_mouse_pos;
}

short Input_System::get_internal_key_code(const Key &key) {
    short key_win = 0;

    if(key >= Key::A && key <= Key::Z) {
        key_win = 'A' + ((short)key - (short)Key::A);
    }
    else if(key >= Key::_0 && key <= Key::_9) {
        key_win = '0' + ((short)key - (short)Key::_0);
    }
    else if(key == Key::SHIFT) {
        key_win = VK_SHIFT;
    }
    else if(key == Key::SPACE) {
        key_win = VK_SPACE;
    }
    else if(key == Key::ENTER) {
        key_win = VK_RETURN;
    }
    else if(key == Key::ESCAPE) {
        key_win = VK_ESCAPE;
    }
    else if(key == Key::LEFT_MOUSE) {
        key_win = VK_LBUTTON;
    }
    else if(key == Key::MIDDLE_MOUSE) {
        key_win = VK_MBUTTON;
    }
    else if(key == Key::RIGHT_MOUSE) {
        key_win = VK_RBUTTON;
    }
   
    return key_win;
}
