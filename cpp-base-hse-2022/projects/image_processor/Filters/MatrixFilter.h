#pragma once
#include "../Image.h"

class MatrixFilter{
public:
    void Apply(Image& image, const std::vector<std::vector<float>> &m);
};
