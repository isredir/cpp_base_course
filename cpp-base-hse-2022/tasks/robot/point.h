#pragma once

#include <cstddef>

struct Point {
    size_t x = 0;
    size_t y = 0;
    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
};
