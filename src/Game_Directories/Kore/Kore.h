#pragma once

#include "../../Game/game_engine.h"
#include "../../Game/i_game_project_manager.h"

class Kore : public I_Game_Project_Manager
{
public:
    Kore();
    ~Kore();
    virtual void update() override;
    virtual void late_update() override;
    virtual void on_create() override;
private:

};