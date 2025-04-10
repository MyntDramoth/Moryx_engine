#include "resource_manager.h"
#include <filesystem>
#include "texture.h"
#include "material.h"
#include "font.h"


Resource_Manager::Resource_Manager(Game* game):game(game) {

}

Resource_Manager::~Resource_Manager() {

}

mesh_sptr Resource_Manager::create_custom_mesh( Vertex_Mesh *vert_list, UINT vert_list_size, UINT *index_list, UINT index_list_size, Material_Slot *material_slot_list, UINT slot_list_size) {
    return std::make_shared<Mesh>(vert_list,vert_list_size,index_list,index_list_size,material_slot_list,slot_list_size,this);
}

mesh_sptr Resource_Manager::create_custom_mesh( Vertex_Mesh *vert_list, UINT vert_list_size, UINT *index_list, UINT index_list_size, Instance_Data *inst_list, UINT instance_list_size, Material_Slot *material_slot_list, UINT slot_list_size) {
    return std::make_shared<Mesh>(vert_list,vert_list_size,index_list,index_list_size,inst_list,instance_list_size,material_slot_list,slot_list_size,this);
}

resource_sptr Resource_Manager::create_resource_from_file_concrete(const wchar_t *file_path)
{

    std::filesystem::path resource_path = file_path;
    auto extension = resource_path.extension();
  
    auto iterator = resources_map.find(file_path);

    if(iterator != resources_map.end()) {
        auto mat = std::dynamic_pointer_cast<Material>(iterator->second);
        if(mat) {
            MORYX_INFO("Found material / material exists");
            return std::make_shared<Material>(mat,this);}
        return iterator->second;
    }

    if(!std::filesystem::exists(resource_path)) {return resource_sptr();}

    resource_sptr resource;

    if(!extension.compare(L".obj")) {
        resource = std::make_shared<Mesh>(resource_path.c_str(),this);
    }
    else if(!extension.compare(L".png") || !extension.compare(L".jpg") || !extension.compare(L".bmp")) {
        resource = std::make_shared<Texture>(resource_path.c_str(),this);
    }
    else if(!extension.compare(L".hlsl") || !extension.compare(L".fx")) {
        resource = std::make_shared<Material>(resource_path.c_str(),this);
    }
    else if(!extension.compare(L".font")) {
        resource = std::make_shared<Font>(resource_path.c_str(),this);
    }

    if(resource) {
        
        resources_map.emplace(file_path,resource);
        return resource;
    }

    return nullptr;
}
