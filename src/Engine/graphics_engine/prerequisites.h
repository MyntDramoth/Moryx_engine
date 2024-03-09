#pragma once

#include <memory>

class Swapchain;
class Index_Buffer;
class Constant_Buffer;
class Vertex_Buffer;
class Vertex_Shader;
class Pixel_Shader;
class Device_Context;
class Render_System;
class Graphics_Engine;
class Resource;
class Resource_Manager;
class Texture_Manager;
class Texture;

typedef std::shared_ptr<Swapchain> swapchain_sptr;
typedef std::shared_ptr<Index_Buffer> index_buffer_sptr;
typedef std::shared_ptr<Constant_Buffer> const_buffer_sptr;
typedef std::shared_ptr<Vertex_Buffer> vert_buffer_sptr;
typedef std::shared_ptr<Vertex_Shader> vert_shader_sptr;
typedef std::shared_ptr<Pixel_Shader> pix_shader_sptr;
typedef std::shared_ptr<Device_Context> device_context_sptr;
typedef std::shared_ptr<Resource> resource_sptr;
typedef std::shared_ptr<Texture> texture_sptr;