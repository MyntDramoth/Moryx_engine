#pragma once

#include "../../Game/game_engine.h"
#include "../../Game/i_game_project_manager.h"

class VET : public I_Game_Project_Manager
{
public:
    VET();
    ~VET();

    virtual void update() override;
    virtual void late_update() override;
    virtual void on_create() override;
private:

};