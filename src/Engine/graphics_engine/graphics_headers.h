#pragma once

#include "compute_shader/compute_shader.h"
#include "constant_buffer/constant_buffer.h"
#include "device_context/device_context.h"
#include "font2D/font2D.h"
#include "index_buffer/index_buffer.h"
#include "material/material.h"
#include "pixel_shader/pixel_shader.h"
#include "render_system/render_system.h"
#include "resource_manager/resource_manager.h"
#include "resource_manager/resource.h"
#include "resource_manager/mesh_manager/mesh_manager.h"
#include "resource_manager/mesh_manager/mesh.h"
#include "resource_manager/texture_manager/texture_manager.h"
#include "resource_manager/texture_manager/texture.h"
#include "resource_manager/font_manager/font_manager.h"
#include "resource_manager/font_manager/font.h"
#include "swapchain/swapchain.h"
#include "vertex_buffer/vertex_buffer.h"
#include "vertex_shader/vertex_shader.h"
#include "prerequisites.h"

//-------------
//MATH
//-------------

#include "../math/matrix4x4.h"
#include "../math/point.h"
#include "../math/rect.h"
#include "../math/vector2D.h"
#include "../math/vector3D.h"
#include "../math/vector4D.h"
#include "../math/vertex_mesh.h"