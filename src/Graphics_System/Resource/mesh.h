#pragma once

#include "resource.h"
#include "../prerequisites.h"

#include "../Graphics/Render_System/Vertex_Buffer/vertex_buffer.h"
#include "../Graphics/Render_System/Index_Buffer/index_buffer.h"
#include "../Graphics/Render_System/Instance_Buffer/instance_buffer.h"

#include  "../Math/vector3D.h"
#include  "../Math/vector2D.h"
#include "../Math/vertex_mesh.h"
#include "../Math/instance_data.h"
#include "material.h"

#include <d3d11.h>
#include <vector>

struct Material_Slot {
    size_t start_index = 0;
    size_t num_indeces = 0;
    size_t material_id = 0;
};

class Mesh : public Resource
{
public:
    Mesh(const wchar_t* full_path, Resource_Manager* manager);
    Mesh(Vertex_Mesh *vert_list, UINT vert_list_size, UINT *index_list, UINT index_list_size, Material_Slot *material_slot_list, UINT slot_list_size, Resource_Manager* manager);
    Mesh(const wchar_t* full_path, Resource_Manager* manager, Instance_Data *inst_list, UINT instance_list_size);
    Mesh(Vertex_Mesh *vert_list, UINT vert_list_size, UINT *index_list, UINT index_list_size, Instance_Data *inst_list, UINT instance_list_size, Material_Slot *material_slot_list, UINT slot_list_size, Resource_Manager* manager);
    
    
    ~Mesh();

    
    Material_Slot get_material_slot(UINT slot);
    size_t get_num_materials();

private:


    void compute_tangents(
        const Vector3D& v0, const Vector3D& v1, const Vector3D& v2,
        const Vector2D& t0, const Vector2D& t1, const Vector2D& t2,
        Vector3D& tangent, Vector3D& binormal
    );

    vert_buffer_sptr vertex_buffer = nullptr;
    index_buffer_sptr index_buffer = nullptr;
    instance_buffer_sptr inst_buffer = nullptr;

    std::vector<Material_Slot> material_slots;

    friend class Device_Context;
    friend class Graphics_Engine;
};