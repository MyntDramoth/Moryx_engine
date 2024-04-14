#pragma once
#include <cmath>

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


    ~Vector3D() {};

    float x,y,z;
};