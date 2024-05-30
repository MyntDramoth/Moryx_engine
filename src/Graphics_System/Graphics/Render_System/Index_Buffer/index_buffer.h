#pragma once

#include <d3d11.h>

#include "../Device_Context/device_context.h"

#include "../../../prerequisites.h"

class Index_Buffer
{
public:
    Index_Buffer(void* indeces, UINT index_size, Render_System* system);
    ~Index_Buffer();

    UINT get_size_index_list();
private:
    UINT indeces_size;

     Microsoft::WRL::ComPtr<ID3D11Buffer> buffer;
    Render_System* render_system {nullptr};
    
    friend class Device_Context;

};
