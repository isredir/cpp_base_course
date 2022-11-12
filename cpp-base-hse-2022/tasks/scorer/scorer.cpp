#include "scorer.h"
#include <algorithm>
#include <unordered_map>

bool CmpEvents(const Event* a, const Event* b) {
    return a->time < b->time;
}

ScoreTable GetScoredStudents(const Events& events, time_t score_time) {
    std::vector<const Event*> events_sorted;
    for (size_t i = 0; i < events.size(); ++i) {
        events_sorted.push_back(&events[i]);
    }
    std::sort(events_sorted.begin(), events_sorted.end(), CmpEvents);
    ScoreTable table = {};
    std::unordered_map<std::string, std::map<std::string, bool>> success;
    std::unordered_map<std::string, std::map<std::string, bool>> open_merge;
    for (const Event* event : events_sorted) {
        if (event->time <= score_time) {
            if (event->event_type == EventType::MergeRequestClosed) {
                open_merge[event->student_name][event->task_name] = false;
                if (success[event->student_name][event->task_name]) {
                    table[event->student_name].insert(event->task_name);
                }
            } else if (event->event_type == EventType::MergeRequestOpen) {
                open_merge[event->student_name][event->task_name] = true;
                if (table[event->student_name].find(event->task_name) != table[event->student_name].end()) {
                    table[event->student_name].erase(event->task_name);
                }
            } else if (event->event_type == EventType::CheckSuccess) {
                success[event->student_name][event->task_name] = true;
                if (!open_merge[event->student_name][event->task_name]) {
                    table[event->student_name].insert(event->task_name);
                }
            } else if (event->event_type == EventType::CheckFailed) {
                success[event->student_name][event->task_name] = false;
                if (table[event->student_name].find(event->task_name) != table[event->student_name].end()) {
                    table[event->student_name].erase(event->task_name);
                }
            }
        } else {
            break;
        }
    }
    ScoreTable res = {};
    for (const Event& event : events) {
        if (!table[event.student_name].empty()) {
            res[event.student_name] = table[event.student_name];
        }
    }
    return res;
}
