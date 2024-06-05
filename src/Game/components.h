#include "../Graphics_System/prerequisites.h"
#include "../Graphics_System/Math/vector3D.h"
#include "../Graphics_System/Math/vector2D.h"
#include "../Graphics_System/Math/matrix4x4.h"
#include "../Graphics_System/Math/rect.h"

#include <vector>

struct Transform {
    Vector3D position;
    Vector3D rotation;
    Vector3D scale = Vector3D(1.0f,1.0f,1.0f);
    Matrix4x4 world_matrix;
};

struct M_Mesh {
    mesh_sptr mesh;
    std::vector<material_sptr> materials;
};