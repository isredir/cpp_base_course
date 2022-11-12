#pragma once

#include "topology.h"

class OverflowTopology : public Topology {
public:
    OverflowTopology(const std::vector<std::vector<bool>> table);
    std::vector<Point> GetNeighbours(const Point& point) const override;
};
