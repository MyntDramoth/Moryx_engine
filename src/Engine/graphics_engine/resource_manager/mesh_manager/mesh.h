#pragma once

#include "../resource.h"
#include "../../prerequisites.h"

#include "../../vertex_buffer/vertex_buffer.h"
#include "../../index_buffer/index_buffer.h"

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
    Mesh(const wchar_t* full_path);
    ~Mesh();

    const vert_buffer_sptr& get_vert_buffer();
    const index_buffer_sptr& get_index_buffer();
    const Material_Slot& get_material_slot(UINT slot);
    size_t get_num_materials();

private:
    vert_buffer_sptr vertex_buffer = nullptr;
    index_buffer_sptr index_buffer = nullptr;

    std::vector<Material_Slot> material_slots;

    friend class Device_Context;
};