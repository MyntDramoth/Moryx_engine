#pragma once

#include <memory>
#include "vector3D.h"

class Matrix4x4 {
public:
    Matrix4x4() {};
   
    void set_identity() {
        memset(matrix,0,sizeof(float) * 16);
        matrix[0][0] = 1.0f;
        matrix[1][1] = 1.0f;
        matrix[2][2] = 1.0f;
        matrix[3][3] = 1.0f;
    };

    void set_translation(const Vector3D &translation) {
        set_identity();
        matrix[3][0] = translation.x;
        matrix[3][1] = translation.y;
        matrix[3][2] = translation.z;
    };

    void set_orthogonal_matrix(float width, float height, float near_plane, float far_plane) {
        set_identity();
        matrix[0][0] = 2.0f/width;
        matrix[1][1] = 2.0f/height;
        matrix[2][2] = 1.0f/(far_plane - near_plane);
        matrix[3][2] = -(near_plane/(far_plane - near_plane));
    };

    void set_scale(const Vector3D &scale) {
        set_identity();
        matrix[0][0] = scale.x;
        matrix[1][1] = scale.y;
        matrix[2][2] = scale.z;
    };

    void set_rotation_x (float x) {
        matrix[1][1] = cos(x);
        matrix[1][2] = sin(x);
        matrix[2][1] = -sin(x);
        matrix[2][2] = cos(x);
    };

    void set_rotation_y (float y) {
        matrix[0][0] = cos(y);
        matrix[0][2] = -sin(y);
        matrix[2][0] = sin(y);
        matrix[2][2] = cos(y);
    };

    void set_rotation_z (float z) {
        matrix[0][0] = cos(z);
        matrix[0][1] = sin(z);
        matrix[1][0] = -sin(z);
        matrix[1][1] = cos(z);
    };

    void operator *=(const Matrix4x4 &in_matrix) {
        Matrix4x4 out;
        for(int i = 0;i<4;i++) {
            for(int j = 0;j<4;j++) { 
                out.matrix[i][j] = 
                (matrix[i][0] * in_matrix.matrix[0][j]) + (matrix[i][1] * in_matrix.matrix[1][j]) +
                (matrix[i][2] * in_matrix.matrix[2][j]) + (matrix[i][3] * in_matrix.matrix[3][j]);

            }
        }
        memcpy(matrix,out.matrix,sizeof(float) * 16);
    };

    ~Matrix4x4() {};

    float matrix[4][4] = {};
};