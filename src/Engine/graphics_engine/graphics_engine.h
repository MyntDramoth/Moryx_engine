#pragma once

#include <d3d11.h>
#include <d3dcompiler.h>

#include "swapchain/swapchain.h"
#include "device_context/device_context.h"
#include "vertex_buffer/vertex_buffer.h"
#include "vertex_shader/vertex_shader.h"
#include "pixel_shader/pixel_shader.h"
#include "constant_buffer/constant_buffer.h"

class Swapchain;
class Constant_Buffer;
class Vertex_Buffer;
class Vertex_Shader;
class Pixel_Shader;
class Device_Context;

class Graphics_Engine {
public:
    Graphics_Engine();
    ~Graphics_Engine();
    bool init();
    bool release();

    static Graphics_Engine* get_engine();
    Device_Context* get_device_context();

    Swapchain * create_swap_chain();
    Constant_Buffer* create_constant_buffer();
    Vertex_Buffer* create_vertex_buffer();
    Vertex_Shader* create_vertex_shader(const void* shader_byte_code, size_t byte_code_size);
    Pixel_Shader* create_pixel_shader(const void* shader_byte_code, size_t byte_code_size);

    bool compile_vertex_shader(const wchar_t* file_name, const char* shader_main_funtion_name, void** shader_byte_code, size_t* byte_code_size);
    bool compile_pixel_shader(const wchar_t* file_name, const char* shader_main_funtion_name, void** shader_byte_code, size_t* byte_code_size);
    void release_compiled_shader();
    //default simple shaders
    
private:
    ID3D11Device* device;
    D3D_FEATURE_LEVEL m_feature_level;
    // or Immediate Device Contact Spider
    Device_Context* device_context;

    IDXGIDevice* dxgi_device;
    IDXGIAdapter* dxgi_adapter;
    IDXGIFactory* dxgi_factory;

    ID3DBlob* shader_blob = nullptr;
    
    friend class Swapchain;
    friend class Constant_Buffer;
    friend class Vertex_Buffer;
    friend class Vertex_Shader;
    friend class Pixel_Shader;
   
};