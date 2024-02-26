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

    float x = 0,y = 0;
};