#include "mesh_manager.h"

Mesh_Manager::Mesh_Manager(): Resource_Manager() {

}

Mesh_Manager::~Mesh_Manager() {

}

mesh_sptr Mesh_Manager::create_mesh_from_file(const wchar_t *file_path)
{
    return std::static_pointer_cast<Mesh>(create_resource_from_file(file_path));
}

mesh_sptr Mesh_Manager::create_mesh(Vertex_Mesh *vert_list, UINT vert_list_size, UINT *index_list, UINT index_list_size, Material_Slot *material_slots, UINT slot_list_size)
{
    Mesh* mesh = nullptr;
    try{
        mesh = new Mesh(vert_list, vert_list_size, index_list, index_list_size,  material_slots, slot_list_size);
    } catch(...){}
    
    mesh_sptr res(mesh);
    return res;
}

Resource *Mesh_Manager::create_resource_from_file_concrete(const wchar_t *file_path)
{
    Mesh* mesh = nullptr;
    try{
        mesh = new Mesh(file_path);
    } catch(...){}

    return mesh;
}
