#pragma once

class Point {
public:
    Point() : x(0),y(0) 
    {};
    Point(const int &X,const int &Y) : x(X),y(Y) 
    {};
    Point(const Point &point) : x(point.x),y(point.y) 
    {};
    ~Point() {};

    int x = 0,y = 0;
};