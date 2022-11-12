#pragma once

#include "topology.h"

class KnightTopology : public Topology {
public:
    KnightTopology(const std::vector<std::vector<bool>>& table);
    std::vector<Point> GetNeighbours(const Point& point) const override;
};
