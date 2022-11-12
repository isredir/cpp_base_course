#include "Mosaic.h"

void Mosaic::ApplyFilter(Image &image, int argc, const char *argv[], int& pos) {
    args = 1;
    IsValid(argc, argv, pos);
    int pixel_size = std::stoi(argv[pos + 1]);
    for (int y = 0; y < image.GetHeight(); y += pixel_size) {
        for (int x = 0; x < image.GetWidth(); x += pixel_size) {
            Color avg;
            for (int i = 0; i < pixel_size; ++i) {
                for (int j = 0; j < pixel_size; ++j) {
                    avg.r += image.At(x + j, y + i).r;
                    avg.g += image.At(x + j, y + i).g;
                    avg.b += image.At(x + j, y + i).b;
                }
            }
            avg.r /= pixel_size * pixel_size;
            avg.g /= pixel_size * pixel_size;
            avg.b /= pixel_size * pixel_size;
            for (int i = 0; i < pixel_size; ++i) {
                for (int j = 0; j < pixel_size; ++j) {
                    if (i <= pixel_size / 20 || j <= pixel_size / 20 || i >= pixel_size - pixel_size / 20 ||
                        j >= pixel_size - pixel_size / 20) {
                        image.At(x + j, y + i) = {0, 0, 0};
                    } else{
                        image.At(x + j, y + i) = avg;
                    }
                }
            }
        }
    }
    pos += 1;
}
