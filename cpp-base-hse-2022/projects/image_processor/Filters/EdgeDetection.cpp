#include "EdgeDetection.h"
#include "GrayScale.h"
#include "MatrixFilter.h"

void EdgeDetection::ApplyFilter(Image& image, int argc, const char *argv[], int& pos) {
    args = 1;
    IsValid(argc, argv, pos);
    float threshold = std::stof(argv[pos + 1]);
    GrayScale gs;
    gs.ApplyFilter(image, argc, argv, pos);
    MatrixFilter mf;
    mf.Apply(image, {{0, -1, 0}, {-1, 4, -1}, {0, -1, 0}});
    for (int y = 0; y < image.GetHeight(); ++y) {
        for (int x = 0; x < image.GetWidth(); ++x) {
            if (image.At(x, y).r > threshold) {
                image.At(x, y) = {1, 1, 1};
            } else {
                image.At(x, y) = {0, 0, 0};
            }
        }
    }
    pos += 1;
}
