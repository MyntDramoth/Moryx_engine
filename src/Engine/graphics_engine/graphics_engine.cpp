#include "graphics_engine.h"


Graphics_Engine::Graphics_Engine()
{
}

Graphics_Engine::~Graphics_Engine()
{
}

bool Graphics_Engine::init()
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

    device_context = new Device_Context(context);

    device->QueryInterface(__uuidof(IDXGIDevice),(void**)&dxgi_device);
    dxgi_device->GetParent(__uuidof(IDXGIAdapter),(void**)&dxgi_adapter);
    dxgi_adapter->GetParent(__uuidof(IDXGIFactory),(void**)&dxgi_factory);



    return true;
}

bool Graphics_Engine::release()
{
    dxgi_device->Release();
    dxgi_adapter->Release();
    dxgi_factory->Release();

    shader_blob->Release();
    
    device_context->release();
    device->Release();
    return true;
}

Graphics_Engine* Graphics_Engine::get_engine()
{
    static Graphics_Engine engine;
    return &engine;
}

Device_Context *Graphics_Engine::get_device_context()
{
    return this->device_context;
}

Swapchain * Graphics_Engine::create_swap_chain()
{
    return new Swapchain();
}

Vertex_Buffer *Graphics_Engine::create_vertex_buffer()
{
    return new Vertex_Buffer();
}

Vertex_Shader *Graphics_Engine::create_vertex_shader(const void *shader_byte_code, size_t byte_code_size) {
    Vertex_Shader* shader = new Vertex_Shader();
    if(!shader->init(shader_byte_code,byte_code_size)) {
        shader->release();
        return nullptr;
    }

    return shader;
}

Pixel_Shader *Graphics_Engine::create_pixel_shader(const void *shader_byte_code, size_t byte_code_size)
{
    Pixel_Shader* shader = new Pixel_Shader();
    if(!shader->init(shader_byte_code,byte_code_size)) {
        shader->release();
        return nullptr;
    }

    return shader;
    
}

bool Graphics_Engine::compile_vertex_shader(const wchar_t* file_name, const char* shader_main_funtion_name, void** shader_byte_code, size_t* byte_code_size) {
    ID3DBlob* err_blob = nullptr;

    HRESULT hres = D3DCompileFromFile(file_name, nullptr, nullptr, shader_main_funtion_name, "vs_5_0", 0,0, &shader_blob, &err_blob);
    if(FAILED(hres)) {
        if(err_blob) {err_blob->Release();}
        return false;
    }
    *shader_byte_code = shader_blob->GetBufferPointer();
    *byte_code_size = shader_blob->GetBufferSize();
    return true;
}

bool Graphics_Engine::compile_pixel_shader(const wchar_t *file_name, const char *shader_main_funtion_name, void **shader_byte_code, size_t *byte_code_size)
{
    ID3DBlob* err_blob = nullptr;

    HRESULT hres = D3DCompileFromFile(file_name, nullptr, nullptr, shader_main_funtion_name, "ps_5_0", 0,0, &shader_blob, &err_blob);
    if(FAILED(hres)) {
        if(err_blob) {err_blob->Release();}
        return false;
    }
    *shader_byte_code = shader_blob->GetBufferPointer();
    *byte_code_size = shader_blob->GetBufferSize();
    return true;
}

void Graphics_Engine::release_compiled_shader() {
    if(shader_blob) {shader_blob->Release();}
}
