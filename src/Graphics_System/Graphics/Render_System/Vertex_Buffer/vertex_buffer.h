#pragma once

#include <d3d11.h>
#include "../Device_Context/device_context.h"

#include "../../../prerequisites.h"


class Vertex_Buffer
{
public:
    Vertex_Buffer(void* vertices, const uint32_t &vertex_size, const uint32_t &vertex_num, const Render_System& system);
    Vertex_Buffer(void* vertices, const uint32_t &vertex_size, const uint32_t &vertex_num, const Render_System& system, const D3D11_BUFFER_DESC &buffer_desc);
    ~Vertex_Buffer();

    uint32_t get_num_vertices();

private:
    uint32_t vert_size;
    uint32_t vert_num;

    Microsoft::WRL::ComPtr<ID3D11Buffer> buffer;
    Microsoft::WRL::ComPtr<ID3D11InputLayout> input_layout;
    const Render_System& m_renderer;

    friend class Device_Context;
};