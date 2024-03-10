#pragma once

#include "../resource_manager.h"
#include "mesh.h"

class Mesh_Manager: public Resource_Manager
{
public:
    Mesh_Manager();
    ~Mesh_Manager();
    mesh_sptr create_mesh_from_file(const wchar_t* file_path);

protected:

    virtual Resource* create_resource_from_file_concrete(const wchar_t* file_path);
private:

};