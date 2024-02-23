#include "index_buffer.h"

Index_Buffer::Index_Buffer() : buffer(0){

}

Index_Buffer::~Index_Buffer() {

}

bool Index_Buffer::load(void *indeces, UINT index_size) {
    
    if(buffer) {buffer->Release();}

    D3D11_BUFFER_DESC buffer_desc = {};
    buffer_desc.Usage = D3D11_USAGE_DEFAULT; //default allows read and write operations by both CPU and GPU
    buffer_desc.ByteWidth = (index_size * 4);
    buffer_desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    buffer_desc.CPUAccessFlags = 0;
    buffer_desc.MiscFlags = 0;

    D3D11_SUBRESOURCE_DATA init_data = {};
    init_data.pSysMem = indeces;


    indeces_size = index_size;
   

    HRESULT hres = Graphics_Engine::get_engine()->device->CreateBuffer(&buffer_desc,&init_data,&buffer);

    if(FAILED(hres)) {
        return false;
    }

    return true;
}

UINT Index_Buffer::get_size_index_list() {
    return this->indeces_size;
}

bool Index_Buffer::release() {
    buffer->Release();
    delete this;
    return true;
}
