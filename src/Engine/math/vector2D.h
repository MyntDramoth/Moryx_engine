#pragma once

class Vector2D {
public:
    Vector2D() : x(0),y(0) 
    {};
    Vector2D(float X, float Y) : x(X),y(Y) 
    {};
    Vector2D(const Vector2D &vect) : x(vect.x),y(vect.y) 
    {};
    ~Vector2D() {};

    
    Vector2D operator +(const Vector2D &in_vect) {
        //Vector3D vect;
       
        return Vector2D( in_vect.x + x,
       in_vect.y + y);
    };

    Vector2D operator -(const Vector2D &in_vect) {
        //Vector3D vect;
        
        return Vector2D(x - in_vect.x,
        y - in_vect.y);
    };

    Vector2D operator *(float num) {
        //Vector3D vect;
        
        return Vector2D(x * num,
        y * num);
    };

    Vector2D operator *(const Vector2D &in_vect) {
        //Vector3D vect;
        
        return Vector2D(x * in_vect.x,
        y * in_vect.y);
    };

    float x = 0,y = 0;
};