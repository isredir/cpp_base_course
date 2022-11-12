#include "robot.h"

robot::Path robot::FindPath(World &world) {
    Path res;
    Point current = world.GetStart();
    Point end = world.GetEnd();
    while (current != end) {
        if (!world.Lookup().empty()) {
            res.push_back(current);
            Topology::Distance min_path = INT_MAX;
            Point next;
            for (auto [p, d] : world.Lookup()) {
                if (d < min_path) {
                    min_path = d;
                    next = p;
                }
            }
            current = next;
            world.Move(next);
        }
        if (current == world.GetStart()) {
            break;
        }
    }
    if (current == end) {
        res.push_back(current);
    }
    return res;
}
