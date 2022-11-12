#include "topology.h"

const Topology::Distance Topology::UNREACHABLE;

Field::Field(const std::vector<std::vector<bool>>& field)
    : height_(field.size()), width_(field[0].size()), field_(field) {
}

size_t Field::GetHeight() const {
    return height_;
}

size_t Field::GetWidth() const {
    return width_;
}

bool Field::At(size_t i, size_t j) const {
    return field_[i][j];
}

Topology::Topology(const std::vector<std::vector<bool>>& table) : table_(Field(table)) {
}

Topology::Distance Topology::MeasureDistance(const Point& from, const Point& to) const {
    if (table_.At(from.y, from.x) || table_.At(to.y, to.x)) {
        return UNREACHABLE;
    }
    std::vector<std::vector<Distance>> paths =
        std::vector<std::vector<Distance>>(table_.GetHeight(), std::vector<Distance>(table_.GetWidth(), INT_MAX));
    std::unordered_set<Point> neighbours;
    neighbours.insert(from);
    paths[from.y][from.x] = 0;
    while (!neighbours.empty()) {
        std::unordered_set<Point> new_neighbours = neighbours;
        for (const Point& point : new_neighbours) {
            neighbours.erase(point);
            for (Point neighbour : GetNeighbours(point)) {
                if (!table_.At(neighbour.y, neighbour.x) && paths[neighbour.y][neighbour.x] == INT_MAX) {
                    neighbours.insert(neighbour);
                    paths[neighbour.y][neighbour.x] = paths[point.y][point.x] + 1;
                }
            }
        }
    }
    if (paths[from.y][from.x] != INT_MAX && paths[to.y][to.x] != INT_MAX) {
        return paths[to.y][to.x];
    }
    return UNREACHABLE;
}

bool Topology::IsPointOnboard(const Point& point) const {
    return point.x >= 0 && point.x < table_.GetWidth() && point.y >= 0 && point.y < table_.GetHeight();
}
std::vector<Point> Topology::GetNeighbours(const Point& point) const {
    return std::vector<Point>();
}
