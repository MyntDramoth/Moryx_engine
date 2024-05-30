#include "pixel_shader.h"

#include <exception>

#include "../render_system.h"

Pixel_Shader::Pixel_Shader(const wchar_t* full_path, const char* entry_point, Render_System* system) : render_system(system)
{
    Microsoft::WRL::ComPtr<ID3DBlob> err_blob {nullptr};
    Microsoft::WRL::ComPtr<ID3DBlob> shader {nullptr};

    

    HRESULT hres = D3DCompileFromFile(full_path, nullptr, nullptr, entry_point, "ps_5_0", 0,0, &shader, &err_blob);
    if(err_blob) {
        MORYX_WARNING("Pixel Shader" << full_path << " compiled with errors:\n" << (char*)err_blob->GetBufferPointer());
    }
    if(!shader) {
        MORYX_ERROR("Pixel Shader" << full_path << " failed to compile!");
    }

    hres = render_system->device->CreatePixelShader(shader->GetBufferPointer(),shader->GetBufferSize(),nullptr,&pixel_shader);
    if(FAILED(hres)) {
        MORYX_ERROR("Failed to create Pixel Shader!");
    }
}

Pixel_Shader::~Pixel_Shader()
{
     
}