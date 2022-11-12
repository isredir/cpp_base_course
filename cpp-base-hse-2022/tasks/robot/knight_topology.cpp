#include "knight_topology.h"

std::vector<Point> KnightTopology::GetNeighbours(const Point& point) const {
    std::vector<Point> res;
    std::vector<std::pair<Distance, Distance>> vec = {{-2, -1}, {-2, 1}, {2, -1}, {2, 1},
                                                      {-1, -2}, {1, -2}, {-1, 2}, {1, 2}};
    for (auto [i, j] : vec) {
        if (IsPointOnboard({point.x + i, point.y + j})) {
            res.push_back({point.x + i, point.y + j});
        }
    }
    return res;
}

KnightTopology::KnightTopology(const std::vector<std::vector<bool>>& table) : Topology(table) {
}
