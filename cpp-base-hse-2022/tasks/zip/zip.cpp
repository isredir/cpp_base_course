#include "zip.h"

Zipped::ZipIter::ZipIter(Iterator it1, Iterator it2, Iterator end1, Iterator end2)
    : first_(it1), second_(it2), first_end_(end1), second_end_(end2) {
}

Zipped::ZipIter& Zipped::ZipIter::operator++() {
    if (first_ != first_end_ && second_ != second_end_) {
        ++first_;
        ++second_;
    }
    if (first_ == first_end_ || second_ == second_end_) {
        first_ = first_end_;
        second_ = second_end_;
    }
    return *this;
}

bool Zipped::ZipIter::operator==(const ZipIter& other) const {
    return first_ == other.first_ && second_ == other.second_;
}

bool Zipped::ZipIter::operator!=(const ZipIter& other) const {
    return !(*this == other);
}

ZippedPair Zipped::ZipIter::operator*() {
    return {*first_, *second_};
}

Zipped::Zipped(Iterator a_begin, Iterator a_end, Iterator b_begin, Iterator b_end)
    : begin_({a_begin, b_begin, a_end, b_end}), end_({a_end, b_end, a_end, b_end}) {
}

Zipped::ZipIter Zipped::begin() const {
    return begin_;
}

Zipped::ZipIter Zipped::end() const {
    return end_;
}

Zipped Zip(Iterator a_begin, Iterator a_end, Iterator b_begin, Iterator b_end) {
    return Zipped(a_begin, a_end, b_begin, b_end);
}