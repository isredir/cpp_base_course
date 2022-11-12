#include "Crop.h"

void Crop::ApplyFilter(Image& image, int argc, const char *argv[], int& pos) {
    args = 2;
    IsValid(argc, argv, pos);
    int new_width = std::stoi(argv[pos + 1]);
    int new_height = std::stoi(argv[pos + 2]);
    if (new_width > image.GetWidth()) {
        new_width = image.GetWidth();
    }
    if (new_height > image.GetHeight()) {
        new_height = image.GetHeight();
    }
    Image new_image = Image{new_width, new_height};
    for (int y = image.GetHeight() - new_height; y < image.GetHeight(); ++y) {
        for (int x = 0; x < new_width; ++x) {
            new_image.At(x, y - (image.GetHeight() - new_height)) = image.At(x, y);
        }
    }
    image = new_image;
    pos += 2;
}
