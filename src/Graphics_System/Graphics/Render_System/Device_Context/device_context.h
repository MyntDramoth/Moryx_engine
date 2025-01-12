#pragma once

#include <d3d11.h>
#include <wrl.h>


#include "../../../prerequisites.h"

class Device_Context
{
public:
    Device_Context(ID3D11DeviceContext* context, Render_System* system);
    ~Device_Context();

    void clear_render_target_color(const swapchain_sptr& swapchain,float red, float green, float blue, float alpha);
    void clear_depth_stencil(const swapchain_sptr& swapchain);

    //void clear_render_target_color(const texture_sptr& render_target,float red, float green, float blue, float alpha);
    //void clear_depth_stencil(const texture_sptr& depth_stencil);

    //void set_render_target(const texture_sptr& render_target,const texture_sptr& depth_stencil);

    void set_vertex_buffer(const vert_buffer_sptr& vertex_buffer);
    void set_instance_and_vertex_buffer(const vert_buffer_sptr& vertex_buffer,const instance_buffer_sptr& instance_buffer);
    void set_instance_buffer(const instance_buffer_sptr& instance_buffer);
    void draw_triangle_list(UINT vertex_count, UINT start_index);
    void draw_indexed_triangle_list(UINT index_count,UINT start_index, UINT vert_start_index);
    void draw_triangle_strip(UINT vertex_count, UINT start_index);
    void draw_indexed_instanced(UINT index_count, UINT instance_count, UINT start_index, INT base_vert_location, UINT start_instance_location);
    void set_viewport_size(UINT width, UINT height);

    void set_index_buffer(const index_buffer_sptr& index_buffer);

    void set_vertex_shader(const vert_shader_sptr& vertex_shader);
    void set_pixel_shader(const pix_shader_sptr& pixel_shader);
    void set_compute_shader(const comp_shader_sptr& compute_shader);

    void set_texture(const texture_internal_sptr* texture, UINT num_textures);
   
    void set_constant_buffer(const vert_shader_sptr& vertex_shader, const const_buffer_sptr& const_buffer);
    void set_constant_buffer(const pix_shader_sptr& pixel_shader, const const_buffer_sptr& const_buffer);
    void set_constant_buffer(const comp_shader_sptr& compute_shader, const const_buffer_sptr& const_buffer);

private:
    Microsoft::WRL::ComPtr<ID3D11DeviceContext> device_context;
    Render_System* render_system {nullptr};

    friend class Constant_Buffer;
    friend class Instance_Buffer;
    friend class Font_Internal;
};