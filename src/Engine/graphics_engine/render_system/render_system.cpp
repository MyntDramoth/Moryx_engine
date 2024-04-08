#include "render_system.h"

#include "../swapchain/swapchain.h"
#include "../device_context/device_context.h"

#include "../vertex_buffer/vertex_buffer.h"
#include "../vertex_shader/vertex_shader.h"
#include "../pixel_shader/pixel_shader.h"
#include "../compute_shader/compute_shader.h"

#include "../constant_buffer/constant_buffer.h"
#include "../index_buffer/index_buffer.h"

#include <exception>
#include <d3dcompiler.h>

Render_System::Render_System() {
    D3D_DRIVER_TYPE driver_types[] = {
        D3D_DRIVER_TYPE_HARDWARE,
        D3D_DRIVER_TYPE_WARP,
        D3D_DRIVER_TYPE_REFERENCE
    };

     UINT num_drivers = ARRAYSIZE(driver_types);

    D3D_FEATURE_LEVEL feature_levels[] = {
        D3D_FEATURE_LEVEL_11_0
    };

    UINT num_feat_levels = ARRAYSIZE(feature_levels);
    HRESULT hres = 0;
   
    for (UINT driver_index = 0; driver_index < num_drivers;) {


        hres = D3D11CreateDevice(NULL,driver_types[driver_index],NULL,NULL,feature_levels,num_feat_levels,D3D11_SDK_VERSION,
        &device,&m_feature_level,&context
        );
        if(SUCCEEDED(hres)) {
            break;
        }

        ++driver_index;
    }

    if(FAILED(hres)) {throw std::exception("failed to create device context!");}
    try {
        device_context = std::make_shared<Device_Context>(context,this);
    } catch(...){}

    device->QueryInterface(__uuidof(IDXGIDevice),(void**)&dxgi_device);
    dxgi_device->GetParent(__uuidof(IDXGIAdapter),(void**)&dxgi_adapter);
    dxgi_adapter->GetParent(__uuidof(IDXGIFactory),(void**)&dxgi_factory);

    intit_rasterizer_state();

}

Render_System::~Render_System() {
    dxgi_device->Release();
    dxgi_adapter->Release();
    dxgi_factory->Release();

    back_face_culling->Release();
    front_face_culling->Release();

    shader_blob->Release();
    context->Release();
    device->Release();
}

device_context_sptr Render_System::get_device_context() {
    return this->device_context;
}

swapchain_sptr Render_System::create_swap_chain(HWND hwnd,UINT width, UINT height) {
    
    swapchain_sptr sc {nullptr};
    try {
        sc = std::make_shared<Swapchain>(hwnd,width,height,this);
    }
    catch(...) {}
    return sc;
}

index_buffer_sptr Render_System::create_index_buffer(void* indeces, UINT index_size) {

   index_buffer_sptr ib {nullptr};
    try {
        ib = std::make_shared<Index_Buffer>(indeces,index_size,this);
    }
    catch (...) {}
    return ib;
}

const_buffer_sptr Render_System::create_constant_buffer(void* buffer, UINT buffer_size) {
    const_buffer_sptr cb {nullptr};
    try {
        cb = std::make_shared<Constant_Buffer>(buffer,buffer_size,this);
    }
    catch (...) {}
    return cb;
}

vert_buffer_sptr Render_System::create_vertex_buffer(void* vertices, UINT vertex_size, UINT vertex_num, void* shader_byte_code, UINT shader_size) {
    vert_buffer_sptr vb {nullptr};
    try {
       vb = std::make_shared<Vertex_Buffer>(vertices,vertex_size,vertex_num,shader_byte_code,shader_size,this);
    }
    catch (...) {}
    return vb;
}

vert_shader_sptr Render_System::create_vertex_shader(const void *shader_byte_code, size_t byte_code_size) {
    vert_shader_sptr shader {nullptr};
    try {
        shader = std::make_shared<Vertex_Shader>(shader_byte_code,byte_code_size, this);
    }
     catch (...) {}

    return shader;
}

pix_shader_sptr Render_System::create_pixel_shader(const void *shader_byte_code, size_t byte_code_size) {
    pix_shader_sptr shader{ nullptr};
    try {
        shader = std::make_shared<Pixel_Shader>(shader_byte_code,byte_code_size, this);
    }
     catch (...) {}

    return shader;
    
}

comp_shader_sptr Render_System::create_compute_shader(const void *shader_byte_code, size_t byte_code_size)
{
    comp_shader_sptr shader{ nullptr};
    try {
        shader = std::make_shared<Compute_Shader>(shader_byte_code,byte_code_size, this);
    }
     catch (...) {}

    return shader;
}

bool Render_System::compile_vertex_shader(const wchar_t* file_name, const char* shader_main_funtion_name, void** shader_byte_code, size_t* byte_code_size) {
    ID3DBlob* err_blob {nullptr};

    HRESULT hres = D3DCompileFromFile(file_name, nullptr, nullptr, shader_main_funtion_name, "vs_5_0", 0,0, &shader_blob, &err_blob);
    if(FAILED(hres)) {
        if(err_blob) {err_blob->Release();}
        return false;
    }
    *shader_byte_code = shader_blob->GetBufferPointer();
    *byte_code_size = shader_blob->GetBufferSize();
    return true;
}

bool Render_System::compile_pixel_shader(const wchar_t *file_name, const char *shader_main_funtion_name, void **shader_byte_code, size_t *byte_code_size) {
    ID3DBlob* err_blob {nullptr};

    HRESULT hres = D3DCompileFromFile(file_name, nullptr, nullptr, shader_main_funtion_name, "ps_5_0", 0,0, &shader_blob, &err_blob);
    if(FAILED(hres)) {
        if(err_blob) {err_blob->Release();}
        return false;
    }
    *shader_byte_code = shader_blob->GetBufferPointer();
    *byte_code_size = shader_blob->GetBufferSize();
    return true;
}

bool Render_System::compile_compute_shader(const wchar_t *file_name, const char *shader_main_funtion_name, void **shader_byte_code, size_t *byte_code_size)
{
    ID3DBlob* err_blob {nullptr};

    HRESULT hres = D3DCompileFromFile(file_name, nullptr, nullptr, shader_main_funtion_name, "ps_5_0", 0,0, &shader_blob, &err_blob);
    if(FAILED(hres)) {
        if(err_blob) {err_blob->Release();}
        return false;
    }
    *shader_byte_code = shader_blob->GetBufferPointer();
    *byte_code_size = shader_blob->GetBufferSize();
    return true;
}

void Render_System::release_compiled_shader() {
    if(shader_blob) {shader_blob->Release();}
}

void Render_System::set_rasterizer_sate(bool front_culling) {
    if(front_culling) {
        context->RSSetState(front_face_culling);
    } else {
        context->RSSetState(back_face_culling);
    }

}

void Render_System::intit_rasterizer_state() {
    D3D11_RASTERIZER_DESC desc = {};
    desc.CullMode = D3D11_CULL_FRONT;
    desc.DepthClipEnable = true;
    desc.FillMode = D3D11_FILL_SOLID;

    device->CreateRasterizerState(&desc,&front_face_culling);

    desc.CullMode = D3D11_CULL_BACK;

    device->CreateRasterizerState(&desc,&back_face_culling);
}
