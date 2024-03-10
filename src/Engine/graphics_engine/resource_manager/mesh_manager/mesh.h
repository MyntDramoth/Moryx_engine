#pragma once

#include "../resource.h"
#include "../../prerequisites.h"

#include "../../vertex_buffer/vertex_buffer.h"
#include "../../index_buffer/index_buffer.h"

#include <d3d11.h>

class Mesh : public Resource
{
public:
    Mesh(const wchar_t* full_path);
    ~Mesh();

    const vert_buffer_sptr& get_vert_buffer();
    const index_buffer_sptr& get_index_buffer();

private:
    vert_buffer_sptr vertex_buffer = nullptr;
    index_buffer_sptr index_buffer = nullptr;

    friend class Device_Context;
};