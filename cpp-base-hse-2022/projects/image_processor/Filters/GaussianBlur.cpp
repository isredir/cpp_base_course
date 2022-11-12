#include "GaussianBlur.h"
#include <cmath>
#include "MatrixFilter.h"

void GaussianBlur::ApplyFilter(Image& image, int argc, const char *argv[], int& pos) {
    args = 1;
    IsValid(argc, argv, pos);
    float sigma = std::stof(argv[pos + 1]);
    float sum = 0;
    int n = static_cast<int>(3 * sigma) + 1;
    std::vector<float> horizontal(2 * n);
    horizontal[0] = 1;
    for (int i = 0; i < n; ++i) {
        horizontal[n + i] = std::exp(static_cast<float>(-i * i) / (2 * sigma * sigma));
        horizontal[n - i] = horizontal[n + i];
        sum += horizontal[n + i] + horizontal[n - i];
    }
    for (int k = -n; k <= n; ++k) {
        horizontal[n + k] /= sum;
    }
    MatrixFilter mf;
    mf.Apply(image, {horizontal});
    std::vector<std::vector<float>> vertical;
    for (int k = -n; k <= n; ++k) {
        vertical.push_back({horizontal[n + k]});
    }
    mf.Apply(image, vertical);
    pos += 1;
}
