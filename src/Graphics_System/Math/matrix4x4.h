#pragma once

#include <memory>
#include "vector3D.h"
#include "vector4D.h"

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

    void set_perspective_FOV(float FOV, float aspect, float near_plane, float far_plane) {
        set_identity();
        float y_scale = 1.0f / tan(FOV/2.0f);
        float x_scale = y_scale/aspect;

        matrix[0][0] = x_scale;
        matrix[1][1] = y_scale;
        matrix[2][2] = far_plane/(far_plane - near_plane);
        matrix[2][3] = 1.0f;
        matrix[3][2] = (-near_plane * far_plane)/(far_plane - near_plane);
        matrix[3][3] = 0.0f;
    };

    void set_scale(const Vector3D& scale) {
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

    Vector3D get_z_direction() {
        return Vector3D(matrix[2][0],matrix[2][1],matrix[2][2]);
    };

    Vector3D get_y_direction() {
        return Vector3D(matrix[1][0],matrix[1][1],matrix[1][2]);
    };

    Vector3D get_x_direction() {
        return Vector3D(matrix[0][0],matrix[0][1],matrix[0][2]);
    };

    Vector3D get_translation() {
        return Vector3D(matrix[3][0],matrix[3][1],matrix[3][2]);
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

    float get_determinant() {
        Vector4D minor, v1,v2,v3;
        float det;
        v1 = Vector4D(this->matrix[0][0],this->matrix[1][0],this->matrix[2][0],this->matrix[3][0]);
        v2 = Vector4D(this->matrix[0][1],this->matrix[1][1],this->matrix[2][1],this->matrix[3][1]);
        v3 = Vector4D(this->matrix[0][2],this->matrix[1][2],this->matrix[2][2],this->matrix[3][2]);

        minor.cross(v1,v2,v3);
        det = -(this->matrix[0][3] * minor.x + this->matrix[1][3] * minor.y + this->matrix[2][3] * minor.z + this->matrix[3][3] * minor.w);
        return det;
    };

    void inverse() {
        int a, i, j;
		Matrix4x4 out;
		Vector4D v, vec[3];
		float det = 0.0f;

		det = this->get_determinant();
		if (!det) {return;}
		for (i = 0; i<4; i++)
		{
			for (j = 0; j<4; j++)
			{
				if (j != i)
				{
					a = j;
					if (j > i) a = a - 1;
					vec[a].x = (this->matrix[j][0]);
					vec[a].y = (this->matrix[j][1]);
					vec[a].z = (this->matrix[j][2]);
					vec[a].w = (this->matrix[j][3]);
				}
			}
			v.cross(vec[0], vec[1], vec[2]);

			out.matrix[0][i] = pow(-1.0f, i) * v.x / det;
			out.matrix[1][i] = pow(-1.0f, i) * v.y / det;
			out.matrix[2][i] = pow(-1.0f, i) * v.z / det;
			out.matrix[3][i] = pow(-1.0f, i) * v.w / det;
		}

        memcpy(matrix, out.matrix, sizeof(float) * 16);
    };

    ~Matrix4x4() {};

    float matrix[4][4] = {};
};