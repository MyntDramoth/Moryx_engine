#pragma once

#include <d3d11.h>
#include <d3dcompiler.h>

#include "swapchain/swapchain.h"
#include "device_context/device_context.h"
#include "vertex_buffer/vertex_buffer.h"

class Swapchain;
class Vertex_Buffer;
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
    Vertex_Buffer* create_vertex_buffer();


    bool create_shaders();
    bool set_shaders();
    void get_shader_buffer_and_size(void ** bytecode, UINT * size);
    
private:
    ID3D11Device* device;
    D3D_FEATURE_LEVEL m_feature_level;
    // or Immediate Device Contact Spider
    Device_Context* device_context;

    IDXGIDevice* dxgi_device;
    IDXGIAdapter* dxgi_adapter;
    IDXGIFactory* dxgi_factory;

    ID3DBlob* vertex_shader_blob;
    ID3DBlob* pixel_shader_blob;
    ID3D11VertexShader* vertex_shader;
    ID3D11PixelShader* pixel_shader;

    friend class Swapchain;
    friend class Vertex_Buffer;
};