#include "Relief.h"
#include "GrayScale.h"

void Relief::ApplyFilter(Image& image, int argc, const char *argv[], int& pos) {
    GrayScale gs;
    gs.ApplyFilter(image, argc, argv, pos);
    Color pre = {0.5, 0.5, 0.5};
    for (int y = 0; y < image.GetHeight(); ++y) {
        for (int x = 0; x < image.GetWidth(); ++x) {
            Color cur = image.At(x, y);
            float r = (cur.r - pre.r) * 1.0f + 0.5f;
            float g = (cur.g - pre.g) * 1.0f + 0.5f;
            float b = (cur.b - pre.b) * 1.0f + 0.5f;
            image.At(x, y) = {r, g, b};
            pre = cur;
        }
    }
}
