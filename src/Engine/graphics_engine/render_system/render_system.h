#pragma once

#include <d3d11.h>

#include "../prerequisites.h"


class Render_System {
public:
    Render_System();
    ~Render_System();

    device_context_sptr get_device_context();

    swapchain_sptr create_swap_chain(HWND hwnd,UINT width, UINT height);
    index_buffer_sptr create_index_buffer(void* indeces, UINT index_size);
    const_buffer_sptr create_constant_buffer(void* buffer, UINT buffer_size);
    vert_buffer_sptr create_vertex_buffer(void* vertices, UINT vertex_size, UINT vertex_num, void* shader_byte_code, UINT shader_size);
    vert_shader_sptr create_vertex_shader(const void* shader_byte_code, size_t byte_code_size);
    pix_shader_sptr create_pixel_shader(const void* shader_byte_code, size_t byte_code_size);

    bool compile_vertex_shader(const wchar_t* file_name, const char* shader_main_funtion_name, void** shader_byte_code, size_t* byte_code_size);
    bool compile_pixel_shader(const wchar_t* file_name, const char* shader_main_funtion_name, void** shader_byte_code, size_t* byte_code_size);
    void release_compiled_shader();
    //default simple shaders
    
private:
    ID3D11Device* device;
    D3D_FEATURE_LEVEL m_feature_level;
    // or Immediate Device Contact Spider
    device_context_sptr device_context {nullptr};

    IDXGIDevice* dxgi_device;
    IDXGIAdapter* dxgi_adapter;
    IDXGIFactory* dxgi_factory;

    ID3DBlob* shader_blob = nullptr;
    
    friend class Swapchain;
    friend class Index_Buffer;
    friend class Constant_Buffer;
    friend class Vertex_Buffer;
    friend class Vertex_Shader;
    friend class Pixel_Shader;
    friend class Texture;
};