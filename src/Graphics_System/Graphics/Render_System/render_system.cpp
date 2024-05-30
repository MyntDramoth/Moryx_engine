#include "render_system.h"

#include "Swapchain/swapchain.h"
#include "Device_Context/device_context.h"

#include "Vertex_Buffer/vertex_buffer.h"
#include "Vertex_Shader/vertex_shader.h"
#include "Pixel_Shader/pixel_shader.h"
#include "Compute_Shader/compute_shader.h"

#include "Constant_Buffer/constant_buffer.h"
#include "Index_Buffer/index_buffer.h"
//#include "font2D/font2D.h"

#include <exception>


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
   
    D3D_FEATURE_LEVEL feature_level = {};

    for (UINT driver_index = 0; driver_index < num_drivers;) {

        
        hres = D3D11CreateDevice(NULL,driver_types[driver_index],NULL,NULL,feature_levels,num_feat_levels,D3D11_SDK_VERSION,
        &device,&feature_level,&context
        );
        if(SUCCEEDED(hres)) {
            break;
        }

        ++driver_index;
    }

    if(FAILED(hres)) {MORYX_ERROR("failed to create device context!");}
    

    device_context = std::make_shared<Device_Context>(context.Get(),this);
  
    device->QueryInterface(__uuidof(IDXGIDevice),(void**)&dxgi_device);
    dxgi_device->GetParent(__uuidof(IDXGIAdapter),(void**)&dxgi_adapter);
    dxgi_adapter->GetParent(__uuidof(IDXGIFactory),(void**)&dxgi_factory);

    intit_rasterizer_state();
    compile_private_shaders();
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
    return std::make_shared<Swapchain>(hwnd,width,height,this); 
}

index_buffer_sptr Render_System::create_index_buffer(void* indeces, UINT index_size) {
    return std::make_shared<Index_Buffer>(indeces,index_size,this);
}

const_buffer_sptr Render_System::create_constant_buffer(void* buffer, UINT buffer_size) {
    return std::make_shared<Constant_Buffer>(buffer,buffer_size,this);
}

vert_buffer_sptr Render_System::create_vertex_buffer(void* vertices, UINT vertex_size, UINT vertex_num) {
    return std::make_shared<Vertex_Buffer>(vertices,vertex_size,vertex_num,this);
}

vert_shader_sptr Render_System::create_vertex_shader(const wchar_t* full_path, const char* entry_point) {
    return std::make_shared<Vertex_Shader>(full_path,entry_point, this);
}

pix_shader_sptr Render_System::create_pixel_shader(const wchar_t* full_path, const char* entry_point) {
    return std::make_shared<Pixel_Shader>(full_path,entry_point, this);
}

comp_shader_sptr Render_System::create_compute_shader(const wchar_t* full_path, const char* entry_point) {
    return std::make_shared<Compute_Shader>(full_path,entry_point, this);
}

texture_internal_sptr Render_System::create_texture(const wchar_t *full_path) {
    return std::make_shared<Texture_Internal>(full_path,this);
}
texture_internal_sptr Render_System::create_texture(const Rect &size, Texture_Internal::Texture_Type tex_type) {
    return std::make_shared<Texture_Internal>(size,tex_type, this);
}
/*
font2D_sptr Render_System::create_font(const wchar_t *file_path)
{
    font2D_sptr font{ nullptr};
     try {
        font = std::make_shared<Font2D>(file_path, this);
    }
    catch (...) {}
    return font;
}*/

// bool Render_System::compile_vertex_shader(const wchar_t* file_name, const char* shader_main_funtion_name, void** shader_byte_code, size_t* byte_code_size) {
//     ID3DBlob* err_blob {nullptr};

//     HRESULT hres = D3DCompileFromFile(file_name, nullptr, nullptr, shader_main_funtion_name, "vs_5_0", 0,0, &shader_blob, &err_blob);
//     if(FAILED(hres)) {
//         if(err_blob) {err_blob->Release();}
//         return false;
//     }
//     *shader_byte_code = shader_blob->GetBufferPointer();
//     *byte_code_size = shader_blob->GetBufferSize();
//     return true;
// }

// bool Render_System::compile_pixel_shader(const wchar_t *file_name, const char *shader_main_funtion_name, void **shader_byte_code, size_t *byte_code_size) {
//     ID3DBlob* err_blob {nullptr};

//     HRESULT hres = D3DCompileFromFile(file_name, nullptr, nullptr, shader_main_funtion_name, "ps_5_0", 0,0, &shader_blob, &err_blob);
//     if(FAILED(hres)) {
//         if(err_blob) {err_blob->Release();}
//         return false;
//     }
//     *shader_byte_code = shader_blob->GetBufferPointer();
//     *byte_code_size = shader_blob->GetBufferSize();
//     return true;
// }

// bool Render_System::compile_compute_shader(const wchar_t *file_name, const char *shader_main_funtion_name, void **shader_byte_code, size_t *byte_code_size) {
//     ID3DBlob* err_blob {nullptr};

//     HRESULT hres = D3DCompileFromFile(file_name, nullptr, nullptr, shader_main_funtion_name, "ps_5_0", 0,0, &shader_blob, &err_blob);
//     if(FAILED(hres)) {
//         if(err_blob) {err_blob->Release();}
//         return false;
//     }
//     *shader_byte_code = shader_blob->GetBufferPointer();
//     *byte_code_size = shader_blob->GetBufferSize();
//     return true;
// }

void Render_System::compile_private_shaders() {
    Microsoft::WRL::ComPtr<ID3DBlob> err_blob {nullptr};
    Microsoft::WRL::ComPtr<ID3DBlob> shader {nullptr};

    auto mesh_layout_code = R"(
        struct VS_INPUT {
            float4 pos: POSITION0;
            float2 uv: TEXCOORD0;
            float3 normal: NORMAL0;
            float3 tangent: TANGENT0;
            float3 binormal: BINORMAL0;
        };

        struct VS_OUTPUT {
            float4 pos :SV_POSITION;
            float2 uv: TEXCOORD0;
            float3 normal: NORMAL0;
            float3 camera_dir: TEXCOORD1;
        };


        VS_OUTPUT main(VS_INPUT input) {
            VS_OUTPUT output = (VS_OUTPUT)0;
            
            return output;   
        }
    )";

    auto code_size = strlen(mesh_layout_code);

    HRESULT hres = D3DCompile(mesh_layout_code,code_size, "vert_mesh_layout",nullptr, nullptr, "main", "vs_5_0", 0,0, &shader, &err_blob);
    if(FAILED(hres)) {
       MORYX_ERROR("Failed to Compile layout shader");
    }
    memcpy(mesh_layout_bytecode,shader->GetBufferPointer(),shader->GetBufferSize());
    mesh_layout_size = shader->GetBufferSize();
}

// void Render_System::release_compiled_shader() {
//     if(shader_blob) {shader_blob->Release();}
// }

void Render_System::set_rasterizer_sate(bool front_culling) {
    if(front_culling) {
        context->RSSetState(front_face_culling.Get());
    } else {
        context->RSSetState(back_face_culling.Get());
    }

}

void Render_System::clear_state() {
    context->ClearState();
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
