#include "index_buffer.h"

#include <exception>
#include "../render_system/render_system.h"

Index_Buffer::Index_Buffer(void* indeces, UINT index_size, Render_System* system) : buffer(0), render_system(system){

    D3D11_BUFFER_DESC buffer_desc = {};
    buffer_desc.Usage = D3D11_USAGE_DEFAULT; //default allows read and write operations by both CPU and GPU
    buffer_desc.ByteWidth = (index_size * 4);
    buffer_desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    buffer_desc.CPUAccessFlags = 0;
    buffer_desc.MiscFlags = 0;

    D3D11_SUBRESOURCE_DATA init_data = {};
    init_data.pSysMem = indeces;


    indeces_size = index_size;
   

    HRESULT hres = render_system->device->CreateBuffer(&buffer_desc,&init_data,&buffer);

    if(FAILED(hres)) {
       throw std::exception("Failed to create Index Buffer!");
    }

}

Index_Buffer::~Index_Buffer() {
    buffer->Release();
}

UINT Index_Buffer::get_size_index_list() {
    return this->indeces_size;
}
