#pragma once
#include <string>
#include "../prerequisites.h"

class Resource
{
public:
    Resource(const wchar_t* full_path, Resource_Manager* manager);
    virtual ~Resource();

protected:
    std::wstring i_full_path;
    Resource_Manager* manager {nullptr};
private:
   
};
