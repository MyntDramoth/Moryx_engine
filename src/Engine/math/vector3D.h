#pragma once


class Vector3D {
public:
    Vector3D() : x(0.0f),y(0.0f),z(0.0f)
    {};
    Vector3D(float X, float Y, float Z) : x(X),y(Y),z(Z)
    {};
    Vector3D(const Vector3D &vector) : x(vector.x),y(vector.y),z(vector.z)
    {};

    static Vector3D lerp(const Vector3D &start,const Vector3D &end, float step) {
        Vector3D vect;
        vect.x = (float)((start.x * (1.0f - step)) + (end.x * (step)));
        vect.y = (float)((start.y * (1.0f - step)) + (end.y * (step)));
        vect.z = (float)((start.z * (1.0f - step)) + (end.z * (step)));
        return vect;
    };

    ~Vector3D() {};

    float x,y,z;
};