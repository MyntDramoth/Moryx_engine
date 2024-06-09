#pragma once

class I_Game_Project_Manager
{
public:
    I_Game_Project_Manager();
    ~I_Game_Project_Manager();

    virtual void update() = 0;
    virtual void late_update() = 0;
    virtual void on_create() = 0;

private:

};