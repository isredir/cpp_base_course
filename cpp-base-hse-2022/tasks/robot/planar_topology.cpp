#include "planar_topology.h"

std::vector<Point> PlanarTopology::GetNeighbours(const Point& point) const {
    std::vector<Point> res;
    std::vector<std::pair<Distance, Distance>> vec = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
    for (auto [i, j] : vec) {
        if (IsPointOnboard({point.x + i, point.y + j})) {
            res.push_back({point.x + i, point.y + j});
        }
    }
    return res;
}

PlanarTopology::PlanarTopology(const std::vector<std::vector<bool>>& table) : Topology(table) {
}
