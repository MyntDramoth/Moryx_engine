#include "device_context.h"

Device_Context::Device_Context(ID3D11DeviceContext* context) : device_context(context) {

}

Device_Context::~Device_Context() {

}

bool Device_Context::clear_render_target_color(Swapchain* swapchain,float red, float green, float blue, float alpha) {
    FLOAT clear_color[] ={red,green,blue,alpha};
    device_context->ClearRenderTargetView(swapchain->target_view,clear_color);
    return true;
}

bool Device_Context::release() {
    device_context->Release();
    delete this;
    return true;
}
