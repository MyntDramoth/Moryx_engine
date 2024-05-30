#pragma once

#include "vector3D.h"

class Vector4D {
public:
    Vector4D() : x(0.0f),y(0.0f),z(0.0f),w(0.0f)
    {};
    Vector4D(float X, float Y, float Z, float W) : x(X),y(Y),z(Z),w(W)
    {};
    Vector4D(const Vector4D &vector) : x(vector.x),y(vector.y),z(vector.z),w(vector.w)
    {};
    Vector4D(const Vector3D &vector) : x(vector.x),y(vector.y),z(vector.z),w(1.0f)
    {};


    static Vector4D lerp(const Vector4D &start,const Vector4D &end, float step) {
        Vector4D vect;
        vect.x = (float)((start.x * (1.0f - step)) + (end.x * (step)));
        vect.y = (float)((start.y * (1.0f - step)) + (end.y * (step)));
        vect.z = (float)((start.z * (1.0f - step)) + (end.z * (step)));
        vect.w = (float)((start.w * (1.0f - step)) + (end.w * (step)));
        return vect;
    };

    void cross(Vector4D &v1,Vector4D &v2,Vector4D &v3) {
        this->x = v1.y * (v2.z * v3.w - v3.z * v2.w) - v1.z * (v2.y * v3.w - v3.y * v2.w) + v1.w * (v2.y * v3.z - v2.z *v3.y);
	    this->y = -(v1.x * (v2.z * v3.w - v3.z * v2.w) - v1.z * (v2.x * v3.w - v3.x * v2.w) + v1.w * (v2.x * v3.z - v3.x * v2.z));
	    this->z = v1.x * (v2.y * v3.w - v3.y * v2.w) - v1.y * (v2.x *v3.w - v3.x * v2.w) + v1.w * (v2.x * v3.y - v3.x * v2.y);
	    this->w = -(v1.x * (v2.y * v3.z - v3.y * v2.z) - v1.y * (v2.x * v3.z - v3.x *v2.z) + v1.z * (v2.x * v3.y - v3.x * v2.y));
    };

    Vector4D operator +(const Vector4D &in_vect) {
        Vector4D vect;
        vect.x = in_vect.x + x;
        vect.y = in_vect.y + y;
        vect.z = in_vect.z + z;
        vect.w = in_vect.w + w;
        return vect;
    };

    Vector4D operator -(const Vector4D &in_vect) {
        Vector4D vect;
        vect.x = x - in_vect.x;
        vect.y = y - in_vect.y;
        vect.z = z - in_vect.z;
        vect.w = w - in_vect.w;
        return vect;
    };

    ~Vector4D() {};

    float x,y,z,w;
};