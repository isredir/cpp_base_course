#include <iostream>
#include "Image.h"
#include "Filters/GaussianBlur.h"

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
    const char* argv[] = {"-blur", "5"};
    GaussianBlur blur;
    blur.ApplyFilter(image, argc, argv, pos);
    if (!IsEqual(image, {{{0.1780, 0.3559, 0.5338}, {0.1926, 0.3852, 0.5778}, {0.2073, 0.4145, 0.6218}},
                         {{0.1780, 0.3559, 0.5338}, {0.1926, 0.3852, 0.5778}, {0.2073, 0.4145, 0.6218}},
                         {{0.1780, 0.3559, 0.5338}, {0.1926, 0.3852, 0.5778}, {0.2073, 0.4145, 0.6218}}})) {
        std::cerr << "Test for \"gaussian blur\" failed..." << std::endl;
        return 1;
    }
    return 0;
}
