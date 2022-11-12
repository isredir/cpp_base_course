#include "Sharpening.h"
#include "MatrixFilter.h"

void Sharpening::ApplyFilter(Image& image, int argc, const char *argv[], int& pos) {
    MatrixFilter mf;
    mf.Apply(image, {{0, -1, 0}, {-1, 5, -1}, {0, -1, 0}});
}
