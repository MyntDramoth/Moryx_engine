#pragma once

#include "../Graphics_System/Math/vector2D.h"
#include "../Graphics_System/Math/rect.h"
#include "../Graphics_System/prerequisites.h"
#include <map>
//#include <Gamepad.h>


class Input_System {
public:
    Input_System();
    ~Input_System();

    void update();
    void lock_cursor(bool lock);
    void set_lock_area(const Rect& area);

    bool is_key_down(const Key& key);
    bool is_key_up(const Key& key);
    Vector2D get_delta_mouse_pos();

private:
    short get_internal_key_code(const Key& key);
    
    short key_state[256] = {};
    short old_key_state[256] = {};
    short final_key_state[256] = {};
    Vector2D old_mouse_pos;
    Vector2D delta_mouse_pos;

    bool is_cursor_locked = false;
    Rect lock_area;
    Vector2D lock_area_center;
    
    

    //std::unique_ptr<DirectX::GamePad> game_pad;
};