#pragma once

#include <d3d11.h>
#include "../swapchain/swapchain.h"
#include "../vertex_buffer/vertex_buffer.h"

class Swapchain;
class Vertex_Buffer;

class Device_Context
{
public:
    Device_Context(ID3D11DeviceContext* context);
    ~Device_Context();

    void clear_render_target_color(Swapchain* swapchain,float red, float green, float blue, float alpha);
    void set_vertex_buffer(Vertex_Buffer* vertex_buffer);
    void draw_triangle_list(UINT vertex_count, UINT start_index);
    void set_viewport_size(UINT width, UINT height);

    bool release();

private:
    ID3D11DeviceContext* device_context;
    
};