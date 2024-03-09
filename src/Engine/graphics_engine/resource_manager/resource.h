#pragma once
#include <string>

class Resource
{
public:
    Resource(const wchar_t* full_path);
    virtual ~Resource();

protected:
    std::wstring i_full_path;
    
private:

};
