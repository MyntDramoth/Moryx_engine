#pragma once

#include <d3d11.h>

#include "../device_context/device_context.h"

#include "../../prerequisites.h"

class Index_Buffer
{
public:
    Index_Buffer(void* indeces, UINT index_size, Render_System* system);
    ~Index_Buffer();

    UINT get_size_index_list();
private:
    UINT indeces_size;

    ID3D11Buffer* buffer;
    Render_System* render_system = nullptr;
    
    friend class Device_Context;

};
