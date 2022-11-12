#include "GrayScale.h"

void GrayScale::ApplyFilter(Image& image, int argc, const char *argv[], int& pos) {
    for (int y = 0; y < image.GetHeight(); ++y) {
        for (int x = 0; x < image.GetWidth(); ++x) {
            float gray = image.At(x, y).r * 0.299f + image.At(x, y).g * 0.578f + image.At(x, y).b * 0.114f;
            image.At(x, y) = {gray, gray, gray};
        }
    }
}

