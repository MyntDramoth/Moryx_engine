#pragma once
#include <cmath>
#include <memory>

constexpr auto M_PI = 3.14159265358979323846;

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

    static Vector3D normalize(const Vector3D& in_vec) {
        Vector3D res;
        float len = std::sqrt((in_vec.x * in_vec.x) + (in_vec.y * in_vec.y) + (in_vec.z * in_vec.z));
        if(!len) {
            return Vector3D();
        }

        res.x = in_vec.x/len;
        res.y = in_vec.y/len;
        res.z = in_vec.z/len;

        return res;
    };

    static Vector3D cross(const Vector3D& vec1, const Vector3D& vec2) {
        Vector3D res;
        res.x = (vec1.y * vec2.z) - (vec1.z * vec2.y);
        res.y = (vec1.z * vec2.x) - (vec1.x * vec2.z);
        res.z = (vec1.x * vec2.y) - (vec1.y * vec2.x);

        return res;
    };

    void operator =(const Vector3D& in_vect) const {
       memcpy((void*)&x,&in_vect.x,sizeof(float));
       memcpy((void*)&y,&in_vect.y,sizeof(float));
       memcpy((void*)&z,&in_vect.z,sizeof(float));
    };

    static Vector3D degrees_to_euler(float x, float y, float z) {
        
        auto to_radians = M_PI/180.0f;
       
        return Vector3D(x * to_radians, y * to_radians, z * to_radians);
    };

    static Vector3D degrees_to_euler(const Vector3D& in_vect) {
        auto to_radians = M_PI/180.0f;
        return in_vect*to_radians;
    };

    Vector3D operator +(const Vector3D& in_vect) const {
       
        return Vector3D( in_vect.x + x,
       in_vect.y + y,
        in_vect.z + z);
    };

    Vector3D operator -(const Vector3D& in_vect) const {
       
        return Vector3D(x - in_vect.x,
        y - in_vect.y,
        z - in_vect.z);
    };

    Vector3D operator *(float num) const {
        //Vector3D vect;
        
        return Vector3D(x * num,
        y * num,
        z * num);
    };

    Vector3D operator *(const Vector3D &in_vect) const {
        //Vector3D vect;
        
        return Vector3D(x * in_vect.x,
        y * in_vect.y,
        z * in_vect.z);
    };

    float operator [](int num) const {
        //Vector3D vect;
        if(num == 0) {return x;}
        if(num == 1) {return y;}
        if(num == 2) {return z;}
        
    };

    ~Vector3D() {};

    float x,y,z;
};