#pragma once

#include "point.h"
#include "topology.h"

#include <exception>
#include <unordered_map>
#include <algorithm>

class World {
public:
    class IllegalMoveException : public std::exception {};

    World(const Topology& topology, Point start, Point end);

    std::unordered_map<Point, Topology::Distance> Lookup() const;

    const Point& GetStart() const;
    const Point& GetEnd() const;
    const Point& GetCurrentPosition() const;

    void Move(const Point& to);

private:
    Point start_;
    Point end_;
    Point cur_;
    const Topology& topology_;
    std::vector<std::vector<bool>> table_;
};
