#include "constant_buffer.h"

Constant_Buffer::Constant_Buffer()
{

}

Constant_Buffer::~Constant_Buffer()
{

}

bool Constant_Buffer::load(void *buffer, UINT buffer_size) {
    if(this->buffer) { this->buffer->Release();}

    D3D11_BUFFER_DESC buffer_desc = {};
    buffer_desc.Usage = D3D11_USAGE_DEFAULT; //default alows read and write operations by both CPU and GPU
    buffer_desc.ByteWidth = buffer_size;
    buffer_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    buffer_desc.CPUAccessFlags = 0;
    buffer_desc.MiscFlags = 0;

    D3D11_SUBRESOURCE_DATA init_data = {};
    init_data.pSysMem = buffer;


    HRESULT hres = Graphics_Engine::get_engine()->device->CreateBuffer(&buffer_desc,&init_data,&this->buffer);

    if(FAILED(hres)) {
        return false;
    }

    return true;
}

bool Constant_Buffer::release() {
    if(buffer) {buffer->Release();}
    delete this;
    return true;
}

void Constant_Buffer::update(Device_Context *context, void *buffer) {
    context->device_context->UpdateSubresource(this->buffer,NULL,NULL,buffer,NULL,NULL);
}
