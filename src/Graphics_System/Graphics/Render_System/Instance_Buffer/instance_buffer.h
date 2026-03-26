#pragma once

#include <d3d11.h>
#include "../Device_Context/device_context.h"

#include "../../../prerequisites.h"
#include "../../../Math/instance_data.h"
#include <vector>

class Instance_Buffer
{
public:
    Instance_Buffer(void* instances, const uint32_t &inst_size, const uint32_t &inst_num, const Render_System& system);
    Instance_Buffer(void* instances, const uint32_t &inst_size, const uint32_t &inst_num, const Render_System& system,const D3D11_BUFFER_DESC &buffer_desc);
    ~Instance_Buffer();

    uint32_t get_num_vertices();
    void UpdateInstanceBuffer(const device_context_sptr &context,const std::vector<Instance_Data> &data);
    
private:
    uint32_t vert_size;
    uint32_t vert_num;

    Microsoft::WRL::ComPtr<ID3D11Buffer> buffer;
    Microsoft::WRL::ComPtr<ID3D11InputLayout> input_layout;
    Microsoft::WRL::ComPtr<ID3D11InputLayout> combined_layout;
    
    const Render_System& m_renderer;

    friend class Device_Context;
};