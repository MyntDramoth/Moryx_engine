#include "vertex_shader.h"

#include <exception>
#include "../render_system.h"

Vertex_Shader::Vertex_Shader(const wchar_t* full_path, const char* entry_point, Render_System *system) : render_system(system) {
    Microsoft::WRL::ComPtr<ID3DBlob> err_blob {nullptr};
    Microsoft::WRL::ComPtr<ID3DBlob> shader {nullptr};

    

    HRESULT hres = D3DCompileFromFile(full_path, nullptr, nullptr, entry_point, "vs_5_0", 0,0, &shader, &err_blob);
    if(err_blob) {
        MORYX_WARNING("Vertex Shader" << full_path << " compiled with errors:\n" << (char*)err_blob->GetBufferPointer());
    }
    if(!shader) {
        MORYX_ERROR("Vertex Shader" << full_path << " failed to compile!");
    }

    hres = render_system->device->CreateVertexShader(shader->GetBufferPointer(),shader->GetBufferSize(),nullptr,&vertex_shader);
    if(FAILED(hres)) {
        MORYX_ERROR("Failed to create Vertex Shader!");
    }
}

Vertex_Shader::~Vertex_Shader() {

}
