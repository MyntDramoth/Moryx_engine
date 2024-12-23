#include "instance_buffer.h"

#include <exception>

#include "../render_system.h"

Instance_Buffer::Instance_Buffer(void* instances, UINT inst_size, UINT inst_num, Render_System* system) : input_layout(0), buffer(0), render_system(system) {
    D3D11_BUFFER_DESC buffer_desc = {};
    buffer_desc.Usage = D3D11_USAGE_DEFAULT; //default alows read and write operations by both CPU and GPU
    buffer_desc.ByteWidth = (inst_size * inst_num);
    buffer_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    buffer_desc.CPUAccessFlags = 0;
    buffer_desc.MiscFlags = 0;

    D3D11_SUBRESOURCE_DATA init_data = {};
    init_data.pSysMem = instances;


    vert_size = inst_size;
    vert_num = inst_num;

    HRESULT hres = render_system->device->CreateBuffer(&buffer_desc,&init_data,&buffer);

    if(FAILED(hres)) {
        MORYX_ERROR("Failed to create Intance Buffer!");
    }

    //that 12 is the size of 3 32bit floats, 1 32bit float being 4 bytes.

    D3D11_INPUT_ELEMENT_DESC layout[] = {
        //SEMANTIC NAME - SEMANTIC INDEX - FORMAT - INPUT SLOT - ALLIGNED BYTE OFFSET - INPUT SLOT CLASS - INSTANCE DATA STEP RATE

        {"INSTANCE_POS", 0, DXGI_FORMAT_R32G32B32_FLOAT, 1, 0, D3D11_INPUT_PER_INSTANCE_DATA, 1},
        {"INSTANCE_UV", 0, DXGI_FORMAT_R32G32_FLOAT, 1, 12, D3D11_INPUT_PER_INSTANCE_DATA, 1}
    };

    UINT layout_size = ARRAYSIZE(layout);

    hres = render_system->device->CreateInputLayout(layout,layout_size,render_system->instance_mesh_layout_bytecode,render_system->instance_mesh_layout_size,&input_layout);
    if(FAILED(hres)) {
       MORYX_ERROR("Failed to create Input Layout!");
    }
}

Instance_Buffer::~Instance_Buffer()
{

}