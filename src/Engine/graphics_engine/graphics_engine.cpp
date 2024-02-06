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

    vertex_shader_blob->Release();
    pixel_shader_blob->Release();
    vertex_shader->Release();
    pixel_shader->Release();

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

bool Graphics_Engine::create_shaders() {
    ID3DBlob* err_blob = nullptr;

    D3DCompileFromFile(L"shader.fx", nullptr, nullptr, "vsmain", "vs_5_0", NULL, NULL, &vertex_shader_blob, &err_blob);
    D3DCompileFromFile(L"shader.fx", nullptr, nullptr, "psmain", "ps_5_0", NULL, NULL, &pixel_shader_blob, &err_blob);
    
    device->CreateVertexShader(vertex_shader_blob->GetBufferPointer(), vertex_shader_blob->GetBufferSize(), nullptr, &vertex_shader);
    device->CreatePixelShader(pixel_shader_blob->GetBufferPointer(), pixel_shader_blob->GetBufferSize(), nullptr, &pixel_shader);
    return true;
    
}

bool Graphics_Engine::set_shaders() {
    device_context->VSSetShader(vertex_shader, nullptr, 0);
    device_context->PSSetShader(pixel_shader, nullptr, 0);
    return true;
}

void Graphics_Engine::get_shader_buffer_and_size(void **bytecode, UINT *size) {
    *bytecode = this->vertex_shader_blob->GetBufferPointer();
    *size = (UINT)this->vertex_shader_blob->GetBufferSize();
}
