#include "compute_shader.h"

#include <exception>

#include "../render_system.h"

Compute_Shader::Compute_Shader(const wchar_t* full_path, const char* entry_point, Render_System* system): render_system(system) {
    Microsoft::WRL::ComPtr<ID3DBlob> err_blob {nullptr};
    Microsoft::WRL::ComPtr<ID3DBlob> shader {nullptr};

    

    HRESULT hres = D3DCompileFromFile(full_path, nullptr, nullptr, entry_point, "cs_5_0", 0,0, &shader, &err_blob);
    if(err_blob) {
        MORYX_WARNING("Compute Shader" << full_path << " compiled with errors:\n" << (char*)err_blob->GetBufferPointer());
    }
    if(!shader) {
        MORYX_ERROR("Compute Shader" << full_path << " failed to compile!");
    }

    hres = render_system->device->CreateComputeShader(shader->GetBufferPointer(),shader->GetBufferSize(),nullptr,&compute_shader);
    if(FAILED(hres)) {
        MORYX_ERROR("Failed to create Compute Shader!");
    }
}

Compute_Shader::~Compute_Shader() {
   
}