#pragma once

#include "../graphics_engine.h"
#include "../device_context/device_context.h"

class Device_Context;

class Index_Buffer
{
public:
    Index_Buffer();
    ~Index_Buffer();

    bool load(void* indeces, UINT index_size);
    UINT get_size_index_list();
    bool release();

private:
    UINT indeces_size;

    ID3D11Buffer* buffer;
    
    friend class Device_Context;

};
