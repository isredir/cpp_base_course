#include <iostream>
#include "Image.h"
#include "Filters/Crop.h"

bool IsEqual(const Image& image, const Image::Matrix matrix) {
    for (int y = 0; y < image.GetHeight(); ++y) {
        for (int x = 0; x < image.GetWidth(); ++x) {
            if (matrix[y][x] != image.At(x, y)) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    Image image(3, 3);
    float value = 1.0f;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            image.At(i, j) = {0.1f * value, 0.2f * value, 0.3f * value};
        }
        ++value;
    }
    int argc = 3;
    int pos = 0;
    const char* argv[] = {"-crop", "2", "2"};
    Crop crop;
    crop.ApplyFilter(image, argc, argv, pos);
    if (!IsEqual(image, {{{0.1, 0.2, 0.3}, {0.2, 0.4, 0.6}}, {{0.1, 0.2, 0.3}, {0.2, 0.4, 0.6}}})) {
        std::cerr << "Test for \"crop\" failed..." << std::endl;
        return 1;
    }
    pos = 0;
    const char* argv1[] = {"-crop", "5", "5"};
    crop.ApplyFilter(image, argc, argv1, pos);
    if (!IsEqual(image, {{{0.1, 0.2, 0.3}, {0.2, 0.4, 0.6}}, {{0.1, 0.2, 0.3}, {0.2, 0.4, 0.6}}})) {
        std::cerr << "Test for \"crop\" failed..." << std::endl;
        return 1;
    }
    return 0;
}
