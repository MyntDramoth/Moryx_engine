#pragma once

#include <d3d11.h>
#include "../device_context/device_context.h"

#include "../../prerequisites.h"


class Vertex_Buffer
{
public:
    Vertex_Buffer(void* vertices, UINT vertex_size, UINT vertex_num, void* shader_byte_code, UINT shader_size, Render_System* system);
    ~Vertex_Buffer();

    UINT get_num_vertices();

private:
    UINT vert_size;
    UINT vert_num;

    ID3D11Buffer* buffer;
    ID3D11InputLayout* input_layout;
    Render_System* system = nullptr;

    friend class Device_Context;
};