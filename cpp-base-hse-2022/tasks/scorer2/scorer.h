#pragma once

#include <map>
#include <set>
#include <string>
#include <vector>
#include <unordered_map>

using StudentName = std::string;
using TaskName = std::string;

using ScoreTable = std::map<StudentName, std::set<TaskName>>;

class Scorer {
public:
    void OnCheckFailed(const StudentName& student_name, const TaskName& task_name);
    void OnCheckSuccess(const StudentName& student_name, const TaskName& task_name);
    void OnMergeRequestOpen(const StudentName& student_name, const TaskName& task_name);
    void OnMergeRequestClosed(const StudentName& student_name, const TaskName& task_name);
    void Reset();
    ScoreTable GetScoreTable() const;

private:
    ScoreTable table_ = {};
    std::unordered_map<StudentName, std::map<TaskName, bool>> success_;
    std::unordered_map<StudentName, std::map<TaskName, bool>> open_merge_;
    void ResetStudent(const StudentName& student);
};
