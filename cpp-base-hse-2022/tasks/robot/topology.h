#pragma once

#include "point.h"
#include <vector>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include "limits.h"
#include <cmath>
#include <iostream>

namespace std {
template <>
struct hash<Point> {
    size_t operator()(const Point& p) const {
        std::size_t seed = 0;

        seed ^= p.x + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        seed ^= p.y + 0x9e3779b9 + (seed << 6) + (seed >> 2);

        return seed;
    }
};
}  // namespace std

class Field {
public:
    Field(const std::vector<std::vector<bool>>& field);
    size_t GetHeight() const;
    size_t GetWidth() const;
    bool At(size_t i, size_t j) const;

private:
    size_t height_;
    size_t width_;
    std::vector<std::vector<bool>> field_;
};

class Topology {
public:
    using Distance = size_t;
    Topology(const std::vector<std::vector<bool>>& table);

    virtual std::vector<Point> GetNeighbours(const Point& point) const;
    Distance MeasureDistance(const Point& from, const Point& to) const;

    static const Distance UNREACHABLE = -1;

protected:
    Field table_;
    bool IsPointOnboard(const Point& point) const;
};
