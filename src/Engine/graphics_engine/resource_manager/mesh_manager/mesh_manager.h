#pragma once

#include "../resource_manager.h"
#include "mesh.h"

class Mesh_Manager: public Resource_Manager
{
public:
    Mesh_Manager();
    ~Mesh_Manager();
    mesh_sptr create_mesh_from_file(const wchar_t* file_path);
    mesh_sptr create_mesh(Vertex_Mesh* vert_list, UINT vert_list_size,  UINT* index_list, UINT index_list_size, Material_Slot* material_slots, UINT slot_list_size);

protected:

    virtual Resource* create_resource_from_file_concrete(const wchar_t* file_path);
private:

};