#include "Image.h"

Color::Color() : r(0), g(0), b(0) {
}

Color::Color(float rr, float gg, float bb) : r(rr), g(gg), b(bb) {
}

Image::Image(int width, int height)
    : width_(width), height_(height), colors_(Matrix(height, std::vector<Color>(width))) {
}

Image::~Image() = default;

bool Image::operator==(const Image &other) const {
    if (height_ != other.height_ || width_ != other.width_) {
        return false;
    }
    for (int y = 0; y < height_; ++y) {
        for (int x = 0; x < width_; ++x) {
            if (At(x, y) != other.At(x, y)) {
                return false;
            }
        }
    }
    return true;
}

int Image::GetWidth() const {
    return width_;
}

int Image::GetHeight() const {
    return height_;
}

Color &Image::At(int x, int y) {
    x = std::clamp(x, 0, width_ - 1);
    y = std::clamp(y, 0, height_ - 1);
    return colors_[y][x];
}

const Color &Image::At(int x, int y) const {
    x = std::clamp(x, 0, width_ - 1);
    y = std::clamp(y, 0, height_ - 1);
    return colors_[y][x];
}

