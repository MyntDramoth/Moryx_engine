#include "device_context.h"

#include <exception>
#include <iostream>
#include "../render_system.h"

#include "../Swapchain/swapchain.h"
#include "../Index_Buffer/index_buffer.h"
#include "../Constant_Buffer/constant_buffer.h"
#include "../Vertex_Buffer/vertex_buffer.h"
#include "../Instance_Buffer/instance_buffer.h"
#include "../Vertex_Shader/vertex_shader.h"
#include "../Pixel_Shader/pixel_shader.h"
#include "../Compute_Shader/compute_shader.h"
#include "../Texture/texture_internal.h"

Device_Context::Device_Context(ID3D11DeviceContext *context, Render_System *system): device_context(context), render_system(system) {

}


Device_Context::~Device_Context() {
    
}

void Device_Context::clear_render_target_color(const swapchain_sptr& swapchain,float red, float green, float blue, float alpha) {
    FLOAT clear_color[] ={red,green,blue,alpha};

    auto tar_view = swapchain->target_view.Get();
    auto sten_view = swapchain->stencil_view.Get();

    device_context->ClearRenderTargetView(tar_view,clear_color);
    device_context->ClearDepthStencilView(sten_view,D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL,1,0);
    device_context->OMSetRenderTargets(1,&tar_view,sten_view);
   
}

void Device_Context::clear_depth_stencil(const swapchain_sptr &swapchain) {
    auto sten_view = swapchain->stencil_view.Get();
    device_context->ClearDepthStencilView(sten_view,D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL,1,0);
}

void Device_Context::set_vertex_buffer(const vert_buffer_sptr& vertex_buffer) {

    UINT stride = vertex_buffer->vert_size;
    UINT offset = 0;

    auto buffer = vertex_buffer->buffer.Get();
    auto layout = vertex_buffer->input_layout.Get();

    device_context->IASetVertexBuffers(0,1,&buffer,&stride,&offset);

    device_context->IASetInputLayout(layout);

   
}

void Device_Context::set_instance_and_vertex_buffer(const vert_buffer_sptr &vertex_buffer, const instance_buffer_sptr &instance_buffer) {
    UINT stride[2] = {vertex_buffer->vert_size,instance_buffer->vert_size};
    UINT offset[2] = {0,0};

    ID3D11Buffer* buffer[2] = {vertex_buffer->buffer.Get(),instance_buffer->buffer.Get()};
    ID3D11InputLayout* layout[2] = {vertex_buffer->input_layout.Get(),instance_buffer->input_layout.Get()};

    device_context->IASetVertexBuffers(0,2,buffer,stride,offset);

    device_context->IASetInputLayout(*layout);
}

void Device_Context::draw_triangle_list(UINT vertex_count, UINT start_index) {
   

    device_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    device_context->Draw(vertex_count,start_index);
}

void Device_Context::draw_indexed_triangle_list(UINT index_count, UINT start_index, UINT vert_start_index) {
    device_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    device_context->DrawIndexed(index_count,start_index,vert_start_index);
}

void Device_Context::draw_triangle_strip(UINT vertex_count, UINT start_index) {
    device_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
    device_context->Draw(vertex_count,start_index);
}

void Device_Context::draw_indexed_instanced(UINT index_count, UINT instance_count, UINT start_index, INT base_vert_location, UINT start_instance_location) {
    device_context->DrawIndexedInstanced(index_count, instance_count, start_index, base_vert_location, start_instance_location);
}

void Device_Context::set_viewport_size(UINT width, UINT height) {
    D3D11_VIEWPORT viewport = {};
    viewport.Width = width;
    viewport.Height = height;
    viewport.MinDepth = 0.0f;
    viewport.MaxDepth = 1.0f;
    

    device_context->RSSetViewports(1,&viewport);
}

void Device_Context::set_index_buffer(const index_buffer_sptr& index_buffer) {
    auto buffer = index_buffer->buffer.Get();
    device_context->IASetIndexBuffer(buffer,DXGI_FORMAT_R32_UINT,0);
}

void Device_Context::set_vertex_shader(const vert_shader_sptr& vertex_shader) {
    auto shader = vertex_shader->vertex_shader.Get();
    device_context->VSSetShader(shader,nullptr,0);
}

void Device_Context::set_pixel_shader(const pix_shader_sptr& pixel_shader) {
    auto shader = pixel_shader->pixel_shader.Get();
    device_context->PSSetShader(shader,nullptr,0);
}

void Device_Context::set_compute_shader(const comp_shader_sptr& compute_shader) {
     auto shader = compute_shader->compute_shader.Get();
     device_context->CSSetShader(shader,nullptr,0);
}

void Device_Context::set_texture(const texture_internal_sptr* texture, UINT num_textures) {
    ID3D11ShaderResourceView* views[32];
    ID3D11SamplerState* samplers[32];
    for(UINT i = 0; i < num_textures;i++) {
        views[i] = texture[i]->shader_view.Get();
        samplers[i] = texture[i]->sampler_state.Get();
    }
    device_context->VSSetShaderResources(0,num_textures, views);
    device_context->VSSetSamplers(0,num_textures,samplers);
    device_context->PSSetShaderResources(0,num_textures, views);
    device_context->PSSetSamplers(0,num_textures,samplers);
}

void Device_Context::set_constant_buffer(const vert_shader_sptr& vertex_shader, const const_buffer_sptr& const_buffer) {
    auto buffer = const_buffer->i_buffer.Get();
    device_context->VSSetConstantBuffers(0,1,&buffer);
}

void Device_Context::set_constant_buffer(const pix_shader_sptr& pixel_shader, const const_buffer_sptr& const_buffer) {
    auto buffer = const_buffer->i_buffer.Get();
    device_context->PSSetConstantBuffers(0,1,&buffer);
}

void Device_Context::set_constant_buffer(const comp_shader_sptr &compute_shader, const const_buffer_sptr &const_buffer) {
    auto buffer = const_buffer->i_buffer.Get();
    device_context->CSSetConstantBuffers(0,1,&buffer);
}
