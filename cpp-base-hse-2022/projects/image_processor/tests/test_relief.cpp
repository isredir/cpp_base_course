#include <iostream>
#include "Image.h"
#include "Filters/Relief.h"

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
    int argc = 1;
    int pos = 0;
    const char* argv[] = {"-rel"};
    Relief rel;
    rel.ApplyFilter(image, argc, argv, pos);
    if (!IsEqual(image, {{{0.1797, 0.1797, 0.1797}, {0.6797, 0.6797, 0.6797}, {0.6797, 0.6797, 0.6797}},
                         {{0.1406, 0.1406, 0.1406}, {0.6797, 0.6797, 0.6797}, {0.6797, 0.6797, 0.6797}},
                         {{0.1406, 0.1406, 0.1406}, {0.6797, 0.6797, 0.6797}, {0.6797, 0.6797, 0.6797}}})) {
        std::cerr << "Test for \"relief\" failed..." << std::endl;
        return 1;
    }
    return 0;
}
