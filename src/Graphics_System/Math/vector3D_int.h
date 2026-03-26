#pragma once
#include <cmath>
#include <memory>

class Vector3D_int {
public:
    Vector3D_int() : x(0.0f),y(0.0f),z(0.0f)
    {};
    Vector3D_int(const int &X,const int &Y,const int &Z) : x(X),y(Y),z(Z)
    {};
    Vector3D_int(const Vector3D_int &vector) : x(vector.x),y(vector.y),z(vector.z)
    {};

    static Vector3D_int lerp(const Vector3D_int &start,const Vector3D_int &end,const int &step) {
        Vector3D_int vect;
        vect.x = (int)((start.x * (1.0f - step)) + (end.x * (step)));
        vect.y = (int)((start.y * (1.0f - step)) + (end.y * (step)));
        vect.z = (int)((start.z * (1.0f - step)) + (end.z * (step)));
        return vect;
    };

    static Vector3D_int normalize(const Vector3D_int& in_vec) {
        Vector3D_int res;
        int len = std::sqrt((in_vec.x * in_vec.x) + (in_vec.y * in_vec.y) + (in_vec.z * in_vec.z));
        if(!len) {
            return Vector3D_int();
        }

        res.x = in_vec.x/len;
        res.y = in_vec.y/len;
        res.z = in_vec.z/len;

        return res;
    };

    static Vector3D_int cross(const Vector3D_int& vec1, const Vector3D_int& vec2) {
        Vector3D_int res;
        res.x = (vec1.y * vec2.z) - (vec1.z * vec2.y);
        res.y = (vec1.z * vec2.x) - (vec1.x * vec2.z);
        res.z = (vec1.x * vec2.y) - (vec1.y * vec2.x);

        return res;
    };

    void operator =(const Vector3D_int& in_vect) const {
       memcpy((void*)&x,&in_vect.x,sizeof(int));
       memcpy((void*)&y,&in_vect.y,sizeof(int));
       memcpy((void*)&z,&in_vect.z,sizeof(int));
    };
    bool operator ==(const Vector3D_int& in_vect) const {
        if(in_vect.x == x && in_vect.y == y && in_vect.z == z) {
            return true;
        } else {return false; }
    };

    Vector3D_int operator +(const Vector3D_int& in_vect) const {
       
        return Vector3D_int( in_vect.x + x,
       in_vect.y + y,
        in_vect.z + z);
    };

    Vector3D_int operator -(const Vector3D_int& in_vect) const {
       
        return Vector3D_int(x - in_vect.x,
        y - in_vect.y,
        z - in_vect.z);
    };

    Vector3D_int operator *(const int &num) const {
        //Vector3D_int vect;
        
        return Vector3D_int(x * num,
        y * num,
        z * num);
    };

    Vector3D_int operator *(const Vector3D_int &in_vect) const {
        //Vector3D_int vect;
        
        return Vector3D_int(x * in_vect.x,
        y * in_vect.y,
        z * in_vect.z);
    };

    float operator [](const int &num) const {
        //Vector3D_int vect;
        if(num == 0) {return x;}
        if(num == 1) {return y;}
        if(num == 2) {return z;}
        
    };

    ~Vector3D_int() {};

    int x,y,z;
};