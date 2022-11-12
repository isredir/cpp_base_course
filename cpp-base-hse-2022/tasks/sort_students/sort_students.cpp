#include "sort_students.h"
#include <algorithm>

bool IsDateGreater(const Student &a, const Student &b) {
    if(a.birth_date.year < b.birth_date.year) {
        return true;
    }
    if(a.birth_date.year > b.birth_date.year) {
        return false;
    }
    if(a.birth_date.month < b.birth_date.month) {
        return true;
    }
    if(a.birth_date.month > b.birth_date.month) {
        return false;
    }
    return a.birth_date.day < b.birth_date.day;
}

bool IsNameGreater(const Student &a, const Student &b) {
    if(a.last_name < b.last_name) {
        return true;
    }
    if(a.last_name > b.last_name) {
        return false;
    }
    return a.name < b.name;
}

bool CmpDate(const Student &a, const Student &b) {
    if(IsDateGreater(a, b)) {
        return true;
    }
    if(IsDateGreater(b, a)) {
        return false;
    }
    if(IsNameGreater(a, b)) {
        return true;
    }
    if(IsNameGreater(b, a)) {
        return false;
    }
    return a.name < b.name;
}

bool CmpName(const Student &a, const Student &b) {
    if(IsNameGreater(a, b)) {
        return true;
    }
    if(IsNameGreater(b, a)) {
        return false;
    }
    if(IsDateGreater(a, b)) {
        return true;
    }
    if(IsDateGreater(b, a)) {
        return false;
    }
    return a.birth_date.day < b.birth_date.day;
}

void SortStudents(std::vector<Student>& students, SortKind sort_kind) {
    if (sort_kind == SortKind::Date) {
        std::sort(students.begin(), students.end(), CmpDate);
    }
    else{
        std::sort(students.begin(), students.end(), CmpName);
    }
}
