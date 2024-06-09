#pragma once

#include "../../Game/game_engine.h"
#include "../../Game/i_game_project_manager.h"

class The_Queen_Must_Grow : public I_Game_Project_Manager
{
public:
    The_Queen_Must_Grow();
    ~The_Queen_Must_Grow();

    virtual void update() override;
    virtual void late_update() override;
    virtual void on_create() override;
private:

};