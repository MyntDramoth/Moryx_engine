#include "vertex_buffer.h"

Vertex_Buffer::Vertex_Buffer() : input_layout(0), buffer(0)
{

}

Vertex_Buffer::~Vertex_Buffer()
{

}

UINT Vertex_Buffer::get_num_vertices()
{
    return this->vert_num;
}

bool Vertex_Buffer::load(void *vertices, UINT vertex_size, UINT vertex_num, void *shader_byte_code, UINT shader_size)
{
    if(input_layout) {input_layout->Release();}
    if(buffer) {buffer->Release();}

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

    HRESULT hres = Graphics_Engine::get_engine()->device->CreateBuffer(&buffer_desc,&init_data,&buffer);

    if(FAILED(hres)) {
        return false;
    }

    //that 12 is the size of 3 32bit floats, 1 32bit float being 4 bytes.

    D3D11_INPUT_ELEMENT_DESC layout[] = {
        //SEMANTIC NAME - SEMANTIC INDEX - FORMAT - INPUT SLOT - ALLIGNED BYTE OFFSET - INPUT SLOT CLASS - INSTANCE DATA STEP RATE
        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0}
    };

    UINT layout_size = ARRAYSIZE(layout);

    hres = Graphics_Engine::get_engine()->device->CreateInputLayout(layout,layout_size,shader_byte_code,shader_size,&input_layout);
    if(FAILED(hres)) {
        return false;
    }
    return true;
}

bool Vertex_Buffer::release()
{
    input_layout->Release();
    buffer->Release();
    delete this;
    return true;
}
