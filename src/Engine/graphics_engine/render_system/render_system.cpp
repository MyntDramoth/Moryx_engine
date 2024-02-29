#include "render_system.h"

#include "../swapchain/swapchain.h"
#include "../device_context/device_context.h"

#include "../vertex_buffer/vertex_buffer.h"
#include "../vertex_shader/vertex_shader.h"
#include "../pixel_shader/pixel_shader.h"

#include "../constant_buffer/constant_buffer.h"
#include "../index_buffer/index_buffer.h"

#include <exception>
#include <d3dcompiler.h>

Render_System::Render_System()
{

}

Render_System::~Render_System()
{

}


bool Render_System::init()
{
    
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
    ID3D11DeviceContext* context;
    for (UINT driver_index = 0; driver_index < num_drivers;) {


        hres = D3D11CreateDevice(NULL,driver_types[driver_index],NULL,NULL,feature_levels,num_feat_levels,D3D11_SDK_VERSION,
        &device,&m_feature_level,&context
        );
        if(SUCCEEDED(hres)) {
            break;
        }

        ++driver_index;
    }

    if(FAILED(hres)) {return false;}
    try {
        device_context = new Device_Context(context,this);
    } catch(...){}

    device->QueryInterface(__uuidof(IDXGIDevice),(void**)&dxgi_device);
    dxgi_device->GetParent(__uuidof(IDXGIAdapter),(void**)&dxgi_adapter);
    dxgi_adapter->GetParent(__uuidof(IDXGIFactory),(void**)&dxgi_factory);



    return true;
}

bool Render_System::release()
{
    dxgi_device->Release();
    dxgi_adapter->Release();
    dxgi_factory->Release();

    shader_blob->Release();
    delete device_context;
    
    device->Release();
    return true;
}

Device_Context* Render_System::get_device_context()
{
    return this->device_context;
}

Swapchain* Render_System::create_swap_chain(HWND hwnd,UINT width, UINT height)
{
    
    Swapchain* sc {nullptr};
    try {
        sc = new Swapchain(hwnd,width,height,this);
    }
    catch(...) {}
    return sc;
}

Index_Buffer* Render_System::create_index_buffer(void* indeces, UINT index_size)
{

    Index_Buffer* ib {nullptr};
    try {
        ib = new Index_Buffer(indeces,index_size,this);
    }
    catch (...) {}
    return ib;
}

Constant_Buffer* Render_System::create_constant_buffer(void* buffer, UINT buffer_size)
{
    Constant_Buffer* cb {nullptr};
    try {
        cb = new Constant_Buffer(buffer,buffer_size,this);
    }
    catch (...) {}
    return cb;
}

Vertex_Buffer* Render_System::create_vertex_buffer(void* vertices, UINT vertex_size, UINT vertex_num, void* shader_byte_code, UINT shader_size)
{
    Vertex_Buffer* vb {nullptr};
    try {
       vb = new Vertex_Buffer(vertices,vertex_size,vertex_num,shader_byte_code,shader_size,this);
    }
    catch (...) {}
    return vb;
}

Vertex_Shader* Render_System::create_vertex_shader(const void *shader_byte_code, size_t byte_code_size) {
    Vertex_Shader* shader {nullptr};
    try {
        shader = new Vertex_Shader(shader_byte_code,byte_code_size, this);
    }
     catch (...) {}

    return shader;
}

Pixel_Shader* Render_System::create_pixel_shader(const void *shader_byte_code, size_t byte_code_size)
{
    Pixel_Shader* shader{ nullptr};
    try {
        shader = new Pixel_Shader(shader_byte_code,byte_code_size, this);
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

bool Render_System::compile_pixel_shader(const wchar_t *file_name, const char *shader_main_funtion_name, void **shader_byte_code, size_t *byte_code_size)
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
