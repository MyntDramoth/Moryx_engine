#include "device_context.h"

#include <exception>
#include "../render_system/render_system.h"

#include "../swapchain/swapchain.h"
#include "../index_buffer/index_buffer.h"
#include "../constant_buffer/constant_buffer.h"
#include "../vertex_buffer/vertex_buffer.h"
#include "../vertex_shader/vertex_shader.h"
#include "../pixel_shader/pixel_shader.h"
#include "../compute_shader/compute_shader.h"
#include "../resource_manager/texture_manager/texture.h"

Device_Context::Device_Context(ID3D11DeviceContext *context, Render_System *system): device_context(context), render_system(system) {

}


Device_Context::~Device_Context() {
    device_context->Release();
}

void Device_Context::clear_render_target_color(const swapchain_sptr& swapchain,float red, float green, float blue, float alpha) {
    FLOAT clear_color[] ={red,green,blue,alpha};
    device_context->ClearRenderTargetView(swapchain->target_view,clear_color);
    device_context->ClearDepthStencilView(swapchain->stencil_view,D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL,1,0);
    device_context->OMSetRenderTargets(1,&swapchain->target_view,swapchain->stencil_view);
   
}

void Device_Context::set_vertex_buffer(const vert_buffer_sptr& vertex_buffer) {

    UINT stride = vertex_buffer->vert_size;
    UINT offset = 0;

    device_context->IASetVertexBuffers(0,1,&vertex_buffer->buffer,&stride,&offset);

    device_context->IASetInputLayout(vertex_buffer->input_layout);

   
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

void Device_Context::set_viewport_size(UINT width, UINT height) {
    D3D11_VIEWPORT viewport = {};
    viewport.Width = width;
    viewport.Height = height;
    viewport.MinDepth = 0.0f;
    viewport.MaxDepth = 1.0f;
    

    device_context->RSSetViewports(1,&viewport);
}

void Device_Context::set_index_buffer(const index_buffer_sptr& index_buffer) {
    device_context->IASetIndexBuffer(index_buffer->buffer,DXGI_FORMAT_R32_UINT,0);
}

void Device_Context::set_vertex_shader(const vert_shader_sptr& vertex_shader) {
    device_context->VSSetShader(vertex_shader->vertex_shader,nullptr,0);
}

void Device_Context::set_pixel_shader(const pix_shader_sptr& pixel_shader) {
    device_context->PSSetShader(pixel_shader->pixel_shader,nullptr,0);
}

void Device_Context::set_compute_shader(const comp_shader_sptr& compute_shader) {
     device_context->CSSetShader(compute_shader->compute_shader,nullptr,0);
}

void Device_Context::set_texture(const vert_shader_sptr& vertex_shader, const texture_sptr* texture, UINT num_textures) {
    ID3D11ShaderResourceView* views[32];
    ID3D11SamplerState* samplers[32];
    for(UINT i = 0; i < num_textures;i++) {
        views[i] = texture[i]->shader_view;
        samplers[i] = texture[i]->sampler_state;
    }
    device_context->VSSetShaderResources(0,num_textures, views);
    device_context->VSSetSamplers(0,num_textures,samplers);
}

void Device_Context::set_texture(const pix_shader_sptr& pixel_shader, const texture_sptr* texture, UINT num_textures) {
    ID3D11ShaderResourceView* views[32];
    ID3D11SamplerState* samplers[32];
    for(UINT i = 0; i < num_textures;i++) {
        views[i] = texture[i]->shader_view;
        samplers[i] = texture[i]->sampler_state;
    }
    device_context->PSSetShaderResources(0,num_textures, views);
    device_context->PSSetSamplers(0,num_textures,samplers);
}

void Device_Context::set_constant_buffer(const vert_shader_sptr& vertex_shader, const const_buffer_sptr& const_buffer) {
    device_context->VSSetConstantBuffers(0,1,&const_buffer->buffer);
}

void Device_Context::set_constant_buffer(const pix_shader_sptr& pixel_shader, const const_buffer_sptr& const_buffer) {
    device_context->PSSetConstantBuffers(0,1,&const_buffer->buffer);
}

void Device_Context::set_constant_buffer(const comp_shader_sptr &compute_shader, const const_buffer_sptr &const_buffer) {
    device_context->CSSetConstantBuffers(0,1,&const_buffer->buffer);
}
