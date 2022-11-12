#include "Negative.h"

void Negative::ApplyFilter(Image& image, int argc, const char *argv[], int& pos) {
    for (int y = 0; y < image.GetHeight(); ++y) {
        for (int x = 0; x < image.GetWidth(); ++x) {
            float nr = 1 - image.At(x, y).r;
            float ng = 1 - image.At(x, y).g;
            float nb = 1 - image.At(x, y).b;
            image.At(x, y) = {nr, ng, nb};
        }
    }
}
