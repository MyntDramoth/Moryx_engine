#pragma once

class Rect {
public:
Rect() : width(0), height(0), left(0), top(0) {}
Rect(int Width, int Height) : width(Width), height(Height), left(0), top(0) {}
Rect(int Width, int Height, int Left, int Top) : width(Width), height(Height), left(Left), top(Top) {}
Rect(const Rect& rect) : width(rect.width), height(rect.height), left(rect.left), top(rect.top) {}

int width, height, left, top;
};