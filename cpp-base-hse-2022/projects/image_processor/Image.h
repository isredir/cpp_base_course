#pragma once
#include <vector>
#include <iostream>
#include <cmath>
#include "BMP.h"

static const float EPSILON = 1.0e-3;

struct Color {
    float r;
    float g;
    float b;
    Color();
    Color(float rr, float gg, float bb);
    bool operator==(const Color& other) const{
        return (std::fabs(r - other.r) < EPSILON) && (std::fabs(g - other.g) < EPSILON) &&
               (std::fabs(b - other.b) < EPSILON);
    }
};

class Image {
public:
    using Matrix = std::vector<std::vector<Color>>;
    Image(int width, int height);
    ~Image();
    int GetWidth() const;
    int GetHeight() const;
    Color& At(int x, int y);
    const Color& At(int x, int y) const;

    bool operator==(const Image& other) const;

private:
    int width_;
    int height_;
    Matrix colors_;
};
