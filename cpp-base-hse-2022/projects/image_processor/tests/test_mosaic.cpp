#include <iostream>
#include "Image.h"
#include "Filters/Mosaic.h"

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
    Image image(4, 4);
    float value = 0.5;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            image.At(i, j) = {0.1f * value, 0.2f * value, 0.3f * value};
        }
        value += 0.5f;
    }
    int argc = 2;
    int pos = 0;
    const char* argv[] = {"-mosaic", "2"};
    Mosaic mosaic;
    mosaic.ApplyFilter(image, argc, argv, pos);
    if (!IsEqual(image, {{{0, 0, 0}, {0, 0, 0},            {0, 0, 0}, {0, 0, 0}},
                         {{0, 0, 0}, {0.075, 0.15, 0.225}, {0, 0, 0}, {0.175, 0.35, 0.525}},
                         {{0, 0, 0}, {0, 0, 0},            {0, 0, 0}, {0, 0, 0}},
                         {{0, 0, 0}, {0.075, 0.15, 0.225}, {0, 0, 0}, {0.175, 0.35, 0.525}}})) {
        std::cerr << "Test for \"mosaic\" failed..." << std::endl;
        return 1;
    }
    return 0;
}
