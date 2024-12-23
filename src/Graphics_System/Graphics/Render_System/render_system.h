#pragma once

#include <d3d11.h>
#include <d3dcompiler.h>
#include <wrl.h>
#include <SpriteBatch.h>
//#include <SpriteSheet.h>

#include "../../prerequisites.h"
#include "Device_Context/device_context.h"
#include "Texture/texture_internal.h"

#include "Swapchain/swapchain.h"

class Render_System {
public:
    Render_System();
    ~Render_System();

    device_context_sptr get_device_context();

    swapchain_sptr create_swap_chain(HWND hwnd,UINT width, UINT height);
    index_buffer_sptr create_index_buffer(void* indeces, UINT index_size);
    const_buffer_sptr create_constant_buffer(void* buffer, UINT buffer_size);
    vert_buffer_sptr create_vertex_buffer(void* vertices, UINT vertex_size, UINT vertex_num);
    instance_buffer_sptr create_instance_buffer(void* instances, UINT inst_size, UINT inst_num);
    
    vert_shader_sptr create_vertex_shader(const wchar_t* full_path, const char* entry_point = "main");
    pix_shader_sptr create_pixel_shader(const wchar_t* full_path, const char* entry_point = "main");
    comp_shader_sptr create_compute_shader(const wchar_t* full_path, const char* entry_point = "main");

    texture_internal_sptr create_texture(const wchar_t* full_path);
    texture_internal_sptr create_texture(const Rect& size, Texture_Internal::Texture_Type tex_type);

    font_internal_sptr create_font(const wchar_t* file_path);

    // bool compile_vertex_shader(const wchar_t* file_name, const char* shader_main_funtion_name, void** shader_byte_code, size_t* byte_code_size);
    // bool compile_pixel_shader(const wchar_t* file_name, const char* shader_main_funtion_name, void** shader_byte_code, size_t* byte_code_size);
    // bool compile_compute_shader(const wchar_t* file_name, const char* shader_main_funtion_name, void** shader_byte_code, size_t* byte_code_size);

    void compile_private_shaders();
    //void release_compiled_shader();
    void set_cull_mode(const CULL_MODE& cull_mode);
    void clear_state();
    void draw_image(const texture_internal_sptr& texture, const Rect& size);

    unsigned char mesh_layout_bytecode[1024];
    unsigned char instance_mesh_layout_bytecode[1024];
    size_t mesh_layout_size = 0;
    size_t instance_mesh_layout_size = 0;
private:

    void intit_rasterizer_state();

    Microsoft::WRL::ComPtr<ID3D11Device> device = nullptr;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext> context = nullptr;
    Microsoft::WRL::ComPtr<ID3D11RasterizerState> front_face_culling = nullptr;
    Microsoft::WRL::ComPtr<ID3D11RasterizerState> back_face_culling = nullptr;
    Microsoft::WRL::ComPtr<ID3D11RasterizerState> none_culling = nullptr;

    Microsoft::WRL::ComPtr<ID3D11BlendState> alpha_blending = nullptr;


    // or Immediate Device Contact Spider
    device_context_sptr device_context {nullptr};
    std::unique_ptr<DirectX::DX11::SpriteBatch> image_batch = nullptr;

    Microsoft::WRL::ComPtr<IDXGIDevice> dxgi_device = nullptr;
    Microsoft::WRL::ComPtr<IDXGIAdapter> dxgi_adapter = nullptr;
    Microsoft::WRL::ComPtr<IDXGIFactory> dxgi_factory = nullptr;

    Microsoft::WRL::ComPtr<ID3DBlob> shader_blob = nullptr;
    
    friend class Swapchain;
    friend class Index_Buffer;
    friend class Constant_Buffer;
    friend class Vertex_Buffer;
    friend class Instance_Buffer;
    friend class Vertex_Shader;
    friend class Pixel_Shader;
    friend class Compute_Shader;
    friend class Texture_Internal;
    friend class Font_Internal;
};