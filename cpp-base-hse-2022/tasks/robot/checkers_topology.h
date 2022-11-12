#pragma once

#include "topology.h"

class CheckersTopology : public Topology {
public:
    CheckersTopology(const std::vector<std::vector<bool>>& table);
    std::vector<Point> GetNeighbours(const Point& point) const override;
};
