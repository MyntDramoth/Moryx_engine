#include "mesh_manager.h"

Mesh_Manager::Mesh_Manager(): Resource_Manager() {

}

Mesh_Manager::~Mesh_Manager() {

}

mesh_sptr Mesh_Manager::create_mesh_from_file(const wchar_t *file_path)
{
    return std::static_pointer_cast<Mesh>(create_resource_from_file(file_path));
}

Resource *Mesh_Manager::create_resource_from_file_concrete(const wchar_t *file_path)
{
    Mesh* mesh = nullptr;
    try{
        mesh = new Mesh(file_path);
    } catch(...){}

    return mesh;
}
