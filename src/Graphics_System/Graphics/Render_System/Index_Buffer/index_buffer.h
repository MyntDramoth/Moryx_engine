#pragma once

#include <d3d11.h>

#include "../Device_Context/device_context.h"

#include "../../../prerequisites.h"

class Index_Buffer
{
public:
    Index_Buffer(void* indeces,const uint32_t &index_size, const Render_System& system);
    Index_Buffer(void* indeces,const uint32_t &index_size, const Render_System& system, const D3D11_BUFFER_DESC &buffer_desc);
    ~Index_Buffer();

    uint32_t get_size_index_list();
private:
    uint32_t indeces_size;

     Microsoft::WRL::ComPtr<ID3D11Buffer> buffer;
    const Render_System& m_renderer;
    
    friend class Device_Context;

};
