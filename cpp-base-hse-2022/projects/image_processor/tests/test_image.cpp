#include <iostream>
#include "Image.h"

bool IsEqual(const Image& image, const Image::Matrix matrix){
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
    Image image1 = image;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            image1.At(i, j) = {0.1f, 0.2f, 0.3f};
        }
        ++value;
    }
    if (image == image1) {
        std::cerr << "Test for \"image\" failed..." << std::endl;
        return 1;
    }
    Image image2(4, 4);
    float value2 = 0.5;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            image2.At(i, j) = {0.1f * value2, 0.2f * value2, 0.3f * value2};
        }
        value += 0.5f;
    }
    if (image == image2) {
        std::cerr << "Test for \"image\" failed..." << std::endl;
        return 1;
    }
    return 0;
}