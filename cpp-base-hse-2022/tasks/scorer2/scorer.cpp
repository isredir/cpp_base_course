#include "scorer.h"

void Scorer::OnCheckFailed(const StudentName& student_name, const TaskName& task_name) {
    success_[student_name][task_name] = false;
    table_[student_name].erase(task_name);
    ResetStudent(student_name);
}

void Scorer::OnCheckSuccess(const StudentName& student_name, const TaskName& task_name) {
    success_[student_name][task_name] = true;
    if (!open_merge_[student_name][task_name]) {
        table_[student_name].insert(task_name);
    }
    ResetStudent(student_name);
}

void Scorer::OnMergeRequestOpen(const StudentName& student_name, const TaskName& task_name) {
    open_merge_[student_name][task_name] = true;
    table_[student_name].erase(task_name);
    ResetStudent(student_name);
}

void Scorer::OnMergeRequestClosed(const StudentName& student_name, const TaskName& task_name) {
    open_merge_[student_name][task_name] = false;
    if (success_[student_name][task_name]) {
        table_[student_name].insert(task_name);
    }
    ResetStudent(student_name);
}

void Scorer::Reset() {
    table_.clear();
    success_.clear();
    open_merge_.clear();
}

ScoreTable Scorer::GetScoreTable() const {
    return table_;
}

void Scorer::ResetStudent(const StudentName& student) {
    if (table_.find(student)->second.empty()) {
        table_.erase(student);
    }
}
