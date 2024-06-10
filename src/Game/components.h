#include "../Graphics_System/prerequisites.h"
#include "../Graphics_System/Math/vector3D.h"
#include "../Graphics_System/Math/vector2D.h"
#include "../Graphics_System/Math/matrix4x4.h"
#include "../Graphics_System/Math/rect.h"

#include <vector>
#include <sstream>

struct Transform {
    Vector3D position;
    Vector3D rotation;
    Vector3D scale = Vector3D(1.0f,1.0f,1.0f);
    Matrix4x4 world_matrix;

    void compute_world_matrix() {
        Matrix4x4 temp;
        temp.set_identity();
        world_matrix.set_identity();

        temp.set_identity();
        temp.set_scale(scale);
        world_matrix *= temp;

        temp.set_identity();
        temp.set_rotation_x(rotation.x);
        world_matrix *= temp;

        temp.set_identity();
        temp.set_rotation_y(rotation.y);
        world_matrix *= temp;

        temp.set_identity();
        temp.set_rotation_z(rotation.z);
        world_matrix *= temp;
        
        world_matrix.set_translation(position);
    }
};

struct M_Mesh {
    mesh_sptr mesh;
    std::vector<material_sptr> materials;
};

struct Camera {
    Matrix4x4 projection_matrix;
    float far_plane = 100.0f;
    float near_plane = 0.01f;
    float FOV = 1.3f;
    Camera_Type type = Camera_Type::PERSPECTIVE;
    Rect screen_area;

    void compute_projection_matrtix() {
        if(type == Camera_Type::PERSPECTIVE) {
            projection_matrix.set_perspective_FOV(FOV,((float)screen_area.width/(float)screen_area.height),near_plane,far_plane);
        }
        else if(type == Camera_Type::ORTHOGONAL) {
            projection_matrix.set_orthogonal_matrix((float)screen_area.width,(float)screen_area.height,near_plane,far_plane);
        }
    }

    Matrix4x4 get_view(Transform t) {
        auto view  = t.world_matrix;
        view.inverse();
        return view;
    }
};

struct Text {
    std::wstring text = L"";
    font_sptr font;
};

struct Light {
    Vector4D color = Vector4D(1.0f,1.0f,1.0f,1.0f);
};

struct Image {
    texture_sptr image;
    Rect size;
};