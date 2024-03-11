#include "vertex_buffer.h"

#include <exception>

#include "../render_system/render_system.h"

Vertex_Buffer::Vertex_Buffer(void* vertices, UINT vertex_size, UINT vertex_num, void* shader_byte_code, UINT shader_size, Render_System* system) : input_layout(0), buffer(0), render_system(system) {
    
    D3D11_BUFFER_DESC buffer_desc = {};
    buffer_desc.Usage = D3D11_USAGE_DEFAULT; //default alows read and write operations by both CPU and GPU
    buffer_desc.ByteWidth = (vertex_size * vertex_num);
    buffer_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    buffer_desc.CPUAccessFlags = 0;
    buffer_desc.MiscFlags = 0;

    D3D11_SUBRESOURCE_DATA init_data = {};
    init_data.pSysMem = vertices;


    vert_size = vertex_size;
    vert_num = vertex_num;

    HRESULT hres = render_system->device->CreateBuffer(&buffer_desc,&init_data,&buffer);

    if(FAILED(hres)) {
        throw std::exception("Failed to create Vertex Buffer!");
    }

    //that 12 is the size of 3 32bit floats, 1 32bit float being 4 bytes.

    D3D11_INPUT_ELEMENT_DESC layout[] = {
        //SEMANTIC NAME - SEMANTIC INDEX - FORMAT - INPUT SLOT - ALLIGNED BYTE OFFSET - INPUT SLOT CLASS - INSTANCE DATA STEP RATE
        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 20, D3D11_INPUT_PER_VERTEX_DATA, 0}
    };

    UINT layout_size = ARRAYSIZE(layout);

    hres = render_system->device->CreateInputLayout(layout,layout_size,shader_byte_code,shader_size,&input_layout);
    if(FAILED(hres)) {
        throw std::exception("Failed to create Input Layout!");
    }
    
}

Vertex_Buffer::~Vertex_Buffer() {
    input_layout->Release();
    buffer->Release();
}

UINT Vertex_Buffer::get_num_vertices() {
    return this->vert_num;
}
