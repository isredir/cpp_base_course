#include "admission.h"
#include <algorithm>
#include <unordered_map>

bool CmpApplicants(const Applicant* a, const Applicant* b) {
    if (a->points != b->points) {
        return a->points > b->points;
    }
    return std::tie(a->student.birth_date.year, a->student.birth_date.month, a->student.birth_date.day,
                    a->student.name) < std::tie(b->student.birth_date.year, b->student.birth_date.month,
                                                b->student.birth_date.day, b->student.name);
}

bool CmpStudents(const Student* a, const Student* b) {
    return std::tie(a->name, a->birth_date.year, a->birth_date.month, a->birth_date.day) <
           std::tie(b->name, b->birth_date.year, b->birth_date.month, b->birth_date.day);
}

AdmissionTable FillUniversities(const std::vector<University>& universities, const std::vector<Applicant>& applicants) {
    std::vector<const Applicant*> a_sorted;
    for (const Applicant& applicant : applicants) {
        a_sorted.push_back(&applicant);
    }
    AdmissionTable res = {};
    std::sort(a_sorted.begin(), a_sorted.end(), CmpApplicants);
    for (const Applicant* person : a_sorted) {
        bool applied = false;
        for (const std::string& wished_univ : person->wish_list) {
            for (const University& univ : universities) {
                if (wished_univ == univ.name && univ.max_students > res[wished_univ].size()) {
                    res[wished_univ].push_back(&person->student);
                    applied = true;
                    break;
                }
            }
            if (applied) {
                break;
            }
        }
    }
    for (auto [key, value] : res) {
        std::sort(value.begin(), value.end(), CmpStudents);
    }
    return res;
}
