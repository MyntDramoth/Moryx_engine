#pragma once

#include "../graphics_engine.h"
#include "../device_context/device_context.h"

class Device_Context;

class Constant_Buffer
{
public:
    Constant_Buffer();
    ~Constant_Buffer();
    
    bool load(void* buffer, UINT buffer_size);
    bool release();
    void update(Device_Context* context, void* buffer);

private:

    ID3D11Buffer* buffer;

    friend class Device_Context;

};
