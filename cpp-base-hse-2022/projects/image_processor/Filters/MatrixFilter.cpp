#include "MatrixFilter.h"

void MatrixFilter::Apply(Image& image, const std::vector<std::vector<float>>& m) {
    Image new_image(image.GetWidth(), image.GetHeight());
    int step_x = m.at(0).size() / 2;
    int step_y = m.size() / 2;
    for (int y = 0; y < image.GetHeight(); ++y) {
        for (int x = 0; x < image.GetWidth(); ++x) {
            float rr = 0;
            float gg = 0;
            float bb = 0;
            for (size_t i = 0; i < m.size(); ++i) {
                for (size_t j = 0; j < m.at(0).size(); ++j) {
                    rr += m[i][j] * image.At(x - step_x + j, y - step_y + i).r;
                    gg += m[i][j] * image.At(x - step_x + j, y - step_y + i).g;
                    bb += m[i][j] * image.At(x - step_x + j, y - step_y + i).b;
                }
            }
            rr = std::clamp(rr, 0.0f, 1.0f);
            gg = std::clamp(gg, 0.0f, 1.0f);
            bb = std::clamp(bb, 0.0f, 1.0f);
            new_image.At(x, y) = {rr, gg, bb};
        }
    }
    image = new_image;
}
