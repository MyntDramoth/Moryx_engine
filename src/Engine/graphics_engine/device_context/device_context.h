#pragma once

#include <d3d11.h>


#include "../prerequisites.h"

class Device_Context
{
public:
    Device_Context(ID3D11DeviceContext* context, Render_System* system);
    ~Device_Context();

    void clear_render_target_color(Swapchain* swapchain,float red, float green, float blue, float alpha);
    void set_vertex_buffer(Vertex_Buffer* vertex_buffer);
    void draw_triangle_list(UINT vertex_count, UINT start_index);
    void draw_indexed_triangle_list(UINT index_count,UINT start_index, UINT vert_start_index);
    void draw_triangle_strip(UINT vertex_count, UINT start_index);
    void set_viewport_size(UINT width, UINT height);

    void set_index_buffer(Index_Buffer* index_buffer);

    void set_vertex_shader(Vertex_Shader* vertex_shader);
    void set_pixel_shader(Pixel_Shader* pixel_shader);

    void set_constant_buffer(Vertex_Shader* vertex_shader, Constant_Buffer* const_buffer);
    void set_constant_buffer(Pixel_Shader* pixel_shader, Constant_Buffer* const_buffer);


private:
    ID3D11DeviceContext* device_context;
    Render_System* render_system {nullptr};

    friend class Constant_Buffer;
    
};