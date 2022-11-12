#include "checkers_topology.h"

std::vector<Point> CheckersTopology::GetNeighbours(const Point& point) const {
    std::vector<Point> res;
    std::vector<std::pair<Distance, Distance>> vec = {{-1, -1}, {1, -1}, {-1, 1}, {1, 1}};
    for (auto [i, j] : vec) {
        if (IsPointOnboard({point.x + i, point.y + j})) {
            res.push_back({point.x + i, point.y + j});
        }
    }
    std::unordered_set<Point> visited;
    std::unordered_set<Point> neighbours_plus;
    neighbours_plus.insert(point);
    while (!neighbours_plus.empty()) {
        std::unordered_set<Point> new_neighbours = neighbours_plus;
        for (const Point& p : new_neighbours) {
            visited.insert(p);
            neighbours_plus.erase(p);
            for (auto [i, j] : vec) {
                if (IsPointOnboard({p.x + 2 * i, p.y + 2 * j}) && table_.At(p.y + j, p.x + i) &&
                    !table_.At(p.y + 2 * j, p.x + 2 * i) && visited.find({p.x + 2 * i, p.y + 2 * j}) == visited.end()) {
                    neighbours_plus.insert({p.x + 2 * i, p.y + 2 * j});
                    res.push_back({p.x + 2 * i, p.y + 2 * j});
                }
            }
        }
    }
    return res;
}

CheckersTopology::CheckersTopology(const std::vector<std::vector<bool>>& table) : Topology(table) {
}
