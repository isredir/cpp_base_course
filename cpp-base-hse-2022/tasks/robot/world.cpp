#include "world.h"

World::World(const Topology& topology, Point start, Point end)
    : start_(start), end_(end), cur_(start), topology_(topology) {
}

std::unordered_map<Point, Topology::Distance> World::Lookup() const {
    std::unordered_map<Point, Topology::Distance> res;
    for (Point point : topology_.GetNeighbours(cur_)) {
        Topology::Distance d = topology_.MeasureDistance(point, end_);
        if (d != Topology::UNREACHABLE) {
            res[point] = d;
        }
    }
    return res;
}

const Point& World::GetStart() const {
    return start_;
}
const Point& World::GetEnd() const {
    return end_;
}
const Point& World::GetCurrentPosition() const {
    return cur_;
}
void World::Move(const Point& to) {
    std::vector<Point> neighbours = topology_.GetNeighbours(cur_);
    if (std::find(neighbours.begin(), neighbours.end(), to) != neighbours.end()) {
        cur_ = to;
        return;
    }
    throw IllegalMoveException();
}
