#pragma once

#include <d3d11.h>
#include "../Device_Context/device_context.h"

#include "../../../prerequisites.h"

class Instance_Buffer
{
public:
    Instance_Buffer(void* instances, UINT inst_size, UINT inst_num, Render_System* system);
    ~Instance_Buffer();

    UINT get_num_vertices();

private:
    UINT vert_size;
    UINT vert_num;

    Microsoft::WRL::ComPtr<ID3D11Buffer> buffer;
    Microsoft::WRL::ComPtr<ID3D11InputLayout> input_layout;
    Microsoft::WRL::ComPtr<ID3D11InputLayout> combined_layout;
    
    Render_System* render_system {nullptr};

    friend class Device_Context;
};