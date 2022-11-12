#include "tests_checking.h"
#include <deque>

std::vector<std::string> StudentsOrder(const std::vector<StudentAction>& student_actions,
                                       const std::vector<size_t>& queries) {
    std::deque<const std::string*> test;
    for (const StudentAction& student : student_actions) {
        if (student.side == Side::Top) {
            test.push_front(&student.name);
        } else {
            test.push_back(&student.name);
        }
    }
    std::vector<std::string> res;
    res.reserve(test.size());
    for (size_t pos : queries) {
        res.push_back(*test[pos - 1]);
    }
    return res;
}
