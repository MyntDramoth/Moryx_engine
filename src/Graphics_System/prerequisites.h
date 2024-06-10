#pragma once

#include <memory>
#include <iostream>
#include <exception>

class Game;
class Input_System;

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
class Texture;
class Texture_Internal;
class Mesh;
class Material;
class Font_Internal;
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
typedef std::shared_ptr<Font_Internal> font_internal_sptr;
typedef std::shared_ptr<Font> font_sptr;


enum class Camera_Type {
    ORTHOGONAL = 0,
    PERSPECTIVE
};

enum class Key{
    A = 0,
    B,C,D,E,F,G, H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9,
    ESCAPE, SHIFT, SPACE, ENTER, LEFT_MOUSE, MIDDLE_MOUSE, RIGHT_MOUSE,
    GAME_PAD_A, GAME_PAD_B, GAME_PAD_DPAD_DOWN, GAME_PAD_DPAD_UP, GAME_PAD_DPAD_LEFT, GAME_PAD_DPAD_RIGHT
};

enum class CULL_MODE {
    NONE = 0,
    FRONT_CULLING,
    BACK_CULLING
};


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