#pragma once

#include <d3d11.h>
#include "../swapchain/swapchain.h"
#include "../index_buffer/index_buffer.h"
#include "../constant_buffer/constant_buffer.h"
#include "../vertex_buffer/vertex_buffer.h"
#include"../vertex_shader/vertex_shader.h"
#include"../pixel_shader/pixel_shader.h"



class Swapchain;
class Index_Buffer;
class Constant_Buffer;
class Vertex_Buffer;
class Vertex_Shader;
class Pixel_Shader;


class Device_Context
{
public:
    Device_Context(ID3D11DeviceContext* context);
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

    bool release();

private:
    ID3D11DeviceContext* device_context;

    friend class Constant_Buffer;
    
};