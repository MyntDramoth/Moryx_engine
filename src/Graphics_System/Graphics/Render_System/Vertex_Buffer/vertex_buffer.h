#pragma once

#include <d3d11.h>
#include "../Device_Context/device_context.h"

#include "../../../prerequisites.h"


class Vertex_Buffer
{
public:
    Vertex_Buffer(void* vertices, UINT vertex_size, UINT vertex_num, Render_System* system);
    ~Vertex_Buffer();

    UINT get_num_vertices();

private:
    UINT vert_size;
    UINT vert_num;

    Microsoft::WRL::ComPtr<ID3D11Buffer> buffer;
    Microsoft::WRL::ComPtr<ID3D11InputLayout> input_layout;
    Render_System* render_system {nullptr};

    friend class Device_Context;
};