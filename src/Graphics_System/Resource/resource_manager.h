#pragma once

#include <unordered_map>
#include <string>
#include "../prerequisites.h"
#include "resource.h"
#include "../../Game/game.h"


class Resource_Manager
{
public:
    Resource_Manager(Game* game);
    ~Resource_Manager();

    template<typename T>
    std::shared_ptr<T> create_resource_from_file(const wchar_t* file_path) {
        return std::dynamic_pointer_cast<T>(create_resource_from_file_concrete(file_path));
    }


    Game* get_game() {return game;}

  
private:
    resource_sptr create_resource_from_file_concrete(const wchar_t* file_path);
    std::unordered_map<std::wstring,resource_sptr> resources_map;
    Game* game {nullptr};
};