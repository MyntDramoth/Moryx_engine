#pragma once

#include <memory>
#include <iostream>
#include <exception>

class Game;

//---------
// GRAPHICS
//---------
class Window;
class Display;
class Graphics_Engine;
class Vertex_Shader;
class Pixel_Shader;
class Compute_Shader;
//---------
// RENDERING
//---------
class Swapchain;
class Index_Buffer;
class Constant_Buffer;
class Vertex_Buffer;
class Device_Context;
class Render_System;

//---------
// RESOURCES
//---------
class Resource;
class Resource_Manager;
class Texture_Manager;
class Texture;
class Texture_Internal;
class Mesh_Manager;
class Mesh;
class Material;
class Font2D;
class Font;

//*********
// POINTERS
//*********

//---------
// GRAPHICS
//---------
typedef std::shared_ptr<Vertex_Shader> vert_shader_sptr;
typedef std::shared_ptr<Pixel_Shader> pix_shader_sptr;
typedef std::shared_ptr<Compute_Shader> comp_shader_sptr;
//---------
// RENDERING
//---------
typedef std::shared_ptr<Device_Context> device_context_sptr;
typedef std::shared_ptr<Swapchain> swapchain_sptr;
typedef std::shared_ptr<Index_Buffer> index_buffer_sptr;
typedef std::shared_ptr<Constant_Buffer> const_buffer_sptr;
typedef std::shared_ptr<Vertex_Buffer> vert_buffer_sptr;
//---------
// RESOURCES
//---------
typedef std::shared_ptr<Resource> resource_sptr;
typedef std::shared_ptr<Texture> texture_sptr;
typedef std::shared_ptr<Texture_Internal> texture_internal_sptr;
typedef std::shared_ptr<Mesh> mesh_sptr;
typedef std::shared_ptr<Material> material_sptr;
typedef std::shared_ptr<Font2D> font2D_sptr;
typedef std::shared_ptr<Font> font_sptr;



//---------
// MACROS
//---------

#define MORYX_ERROR(message)\
{\
    std::wclog << "Moryx Error: " << message <<std::endl;\
    throw std::runtime_error("");\
}

#define MORYX_WARNING(message)\
{\
    std::wclog << "Moryx Warning: " << message <<std::endl;\
}

#define MORYX_INFO(message)\
{\
    std::wclog << "Moryx Info: " << message <<std::endl;\
}