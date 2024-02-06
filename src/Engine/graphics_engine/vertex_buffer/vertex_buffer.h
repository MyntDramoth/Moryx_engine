#pragma once

#include "../graphics_engine.h"
#include "../device_context/device_context.h"

class Device_Context;

class Vertex_Buffer
{
public:
    Vertex_Buffer();
    ~Vertex_Buffer();

    UINT get_num_vertices();
    bool load(void* vertices, UINT vertex_size, UINT vertex_num, void* shader_byte_code, UINT shader_size);
    bool release();

private:
    UINT vert_size;
    UINT vert_num;

    ID3D11Buffer* buffer;
    ID3D11InputLayout* input_layout;

    friend class Device_Context;
};