#pragma once

class Rectangle {
    int width_, height_;
public:
    Rectangle(int width, int height);

    int GetArea() const;
    int GetPerimeter() const;
    int GetWidth() const;
    int GetHeight() const;
};
