#pragma once

class Input_Listener {
public:
    Input_Listener() {

    };

    ~Input_Listener() {

    };

    //KEYBOARD - Pure Virtual Callback Functions
    virtual void on_key_down(int key) = 0;
    virtual void on_key_up(int key) = 0;
};