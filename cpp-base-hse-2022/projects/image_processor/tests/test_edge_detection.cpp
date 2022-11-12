#include <iostream>
#include "Image.h"
#include "Filters/EdgeDetection.h"

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
    int argc = 2;
    int pos = 0;
    const char* argv[] = {"-edge", "0.05"};
    EdgeDetection edge;
    edge.ApplyFilter(image, argc, argv, pos);
    if (!IsEqual(image, {{{0, 0, 0}, {0, 0, 0}, {1, 1, 1}},
                         {{0, 0, 0}, {0, 0, 0}, {1, 1, 1}},
                         {{0, 0, 0}, {0, 0, 0}, {1, 1, 1}}})) {
        std::cerr << "Test for \"edge detection\" failed..." << std::endl;
        return 1;
    }
    return 0;
}
