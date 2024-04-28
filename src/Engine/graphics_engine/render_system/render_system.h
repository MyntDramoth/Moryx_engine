#pragma once

#include <d3d11.h>

#include "../prerequisites.h"
#include "../device_context/device_context.h"

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
    comp_shader_sptr create_compute_shader(const void* shader_byte_code, size_t byte_code_size);

    font2D_sptr create_font(const wchar_t* file_path);

    bool compile_vertex_shader(const wchar_t* file_name, const char* shader_main_funtion_name, void** shader_byte_code, size_t* byte_code_size);
    bool compile_pixel_shader(const wchar_t* file_name, const char* shader_main_funtion_name, void** shader_byte_code, size_t* byte_code_size);
    bool compile_compute_shader(const wchar_t* file_name, const char* shader_main_funtion_name, void** shader_byte_code, size_t* byte_code_size);
    void release_compiled_shader();
    void set_rasterizer_sate(bool front_culling);
    void clear_state();
    //default simple shaders
    
private:

    void intit_rasterizer_state();


    ID3D11Device* device = nullptr;
    ID3D11DeviceContext* context = nullptr;
    ID3D11RasterizerState* front_face_culling = nullptr;
    ID3D11RasterizerState* back_face_culling = nullptr;

    D3D_FEATURE_LEVEL m_feature_level;
    // or Immediate Device Contact Spider
    device_context_sptr device_context {nullptr};

    IDXGIDevice* dxgi_device = nullptr;
    IDXGIAdapter* dxgi_adapter = nullptr;
    IDXGIFactory* dxgi_factory = nullptr;

    ID3DBlob* shader_blob = nullptr;
    
    friend class Swapchain;
    friend class Index_Buffer;
    friend class Constant_Buffer;
    friend class Vertex_Buffer;
    friend class Vertex_Shader;
    friend class Pixel_Shader;
    friend class Compute_Shader;
    friend class Texture;
    friend class Font2D;
};