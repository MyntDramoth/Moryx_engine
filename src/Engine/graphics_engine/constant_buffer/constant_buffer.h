#pragma once

#include "../device_context/device_context.h"

#include <d3d11.h>

#include "../prerequisites.h"

class Constant_Buffer
{
public:
    Constant_Buffer(void* buffer, UINT buffer_size, Render_System *system);
    ~Constant_Buffer();
    
    void update(device_context_sptr context, void* buffer);

private:

    ID3D11Buffer* buffer;
    Render_System* render_system {nullptr};

    friend class Device_Context;

};
