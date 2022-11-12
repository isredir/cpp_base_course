#include "overflow_topology.h"

std::vector<Point> OverflowTopology::GetNeighbours(const Point& point) const {
    std::vector<Point> res;
    std::vector<std::pair<Distance, Distance>> vec = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
    for (auto [i, j] : vec) {
        if (IsPointOnboard({point.x + i, point.y + j})) {
            res.push_back({point.x + i, point.y + j});
        }
    }
    if (point.x == 0) {
        res.push_back({table_.GetWidth() - 1, point.y});
    }
    if (point.y == 0) {
        res.push_back({point.x, table_.GetHeight() - 1});
    }
    if (point.x == table_.GetWidth() - 1) {
        res.push_back({0, point.y});
    }
    if (point.y == table_.GetHeight() - 1) {
        res.push_back({point.x, 0});
    }
    return res;
}

OverflowTopology::OverflowTopology(const std::vector<std::vector<bool>> table) : Topology(table) {
}
