#pragma once

#include <unordered_map>
#include <string>
#include "../prerequisites.h"
#include "resource.h"

class Resource_Manager
{
public:
    Resource_Manager();
    virtual ~Resource_Manager();

    resource_sptr create_resource_from_file(const wchar_t* file_path);

protected:
    virtual Resource* create_resource_from_file_concrete(const wchar_t* file_path) = 0;

private:
    std::unordered_map<std::wstring,resource_sptr> resources_map;
};