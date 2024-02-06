#include "device_context.h"

Device_Context::Device_Context(ID3D11DeviceContext* context) : device_context(context) {

}

Device_Context::~Device_Context() {

}

void Device_Context::clear_render_target_color(Swapchain* swapchain,float red, float green, float blue, float alpha) {
    FLOAT clear_color[] ={red,green,blue,alpha};
    device_context->ClearRenderTargetView(swapchain->target_view,clear_color);
    device_context->OMSetRenderTargets(1,&swapchain->target_view,NULL);
   
}

void Device_Context::set_vertex_buffer(Vertex_Buffer *vertex_buffer) {

    UINT stride = vertex_buffer->vert_size;
    UINT offset = 0;

    device_context->IASetVertexBuffers(0,1,&vertex_buffer->buffer,&stride,&offset);

    device_context->IASetInputLayout(vertex_buffer->input_layout);

   
}

void Device_Context::draw_triangle_list(UINT vertex_count, UINT start_index) {
   

    device_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

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

bool Device_Context::release() {
    device_context->Release();
    delete this;
    return true;
}
