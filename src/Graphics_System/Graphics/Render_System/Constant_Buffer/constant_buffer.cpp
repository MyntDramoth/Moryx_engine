#include "constant_buffer.h"

#include "../render_system.h"
#include <exception>

Constant_Buffer::Constant_Buffer(void* buffer, UINT buffer_size, Render_System *system) : render_system(system) {
   

    D3D11_BUFFER_DESC buffer_desc = {};
    buffer_desc.Usage = D3D11_USAGE_DEFAULT; //default alows read and write operations by both CPU and GPU
    buffer_desc.ByteWidth = buffer_size;
    buffer_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    buffer_desc.CPUAccessFlags = 0;
    buffer_desc.MiscFlags = 0;

    D3D11_SUBRESOURCE_DATA init_data = {};
    init_data.pSysMem = buffer;


    HRESULT hres = render_system->device->CreateBuffer(&buffer_desc,&init_data,&this->i_buffer);

    if(FAILED(hres)) {
        MORYX_ERROR("Failed to create Constant Buffer!");
    }
}

Constant_Buffer::~Constant_Buffer()
{
   
}

void Constant_Buffer::update(device_context_sptr context, void *buffer) {
    context->device_context->UpdateSubresource(this->i_buffer.Get(),NULL,NULL,buffer,NULL,NULL);
}
