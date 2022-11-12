#pragma once

#include <iterator>
#include <utility>

template <typename Sequence1, typename Sequence2>
class Zipped {
public:
    using Iterator1 = decltype(std::begin(std::declval<Sequence1&>()));
    using Iterator2 = decltype(std::begin(std::declval<Sequence2&>()));
    using ZippedPair =
        std::pair<decltype(*std::begin(std::declval<Sequence1&>())), decltype(*std::begin(std::declval<Sequence2&>()))>;
    class ZipIter {
    public:
        ZipIter(Iterator1 it1, Iterator2 it2) : first_(it1), second_(it2) {
        }
        ZipIter& operator++() {
            ++first_;
            ++second_;
            return *this;
        }
        bool operator!=(const ZipIter& other) {
            if (first_ == other.first_ || second_ == other.second_) {
                first_ = other.first_;
                second_ = other.second_;
            }
            return first_ != other.first_ || second_ != other.second_;
        }
        ZippedPair operator*() {
            return {*first_, *second_};
        }

    private:
        Iterator1 first_;
        Iterator2 second_;
    };
    Zipped(Iterator1 a_begin, Iterator1 a_end, Iterator2 b_begin, Iterator2 b_end)
        : begin_({a_begin, b_begin}), end_({a_end, b_end}) {
    }
    ZipIter begin() const {  // NOLINT
        return begin_;
    }
    ZipIter end() const {  // NOLINT
        return end_;
    }

private:
    ZipIter begin_;
    ZipIter end_;
};

template <typename Sequence1, typename Sequence2>
auto Zip(const Sequence1& sequence1, const Sequence2& sequence2) {
    auto a_begin = std::begin(sequence1);
    auto a_end = std::end(sequence1);
    auto b_begin = std::begin(sequence2);
    auto b_end = std::end(sequence2);
    return Zipped<const Sequence1&, const Sequence2&>(a_begin, a_end, b_begin, b_end);
}

template <typename Sequence>
auto Begin(Sequence& sequence) {
    using Iterator = decltype(std::begin(std::declval<Sequence&>()));
    Iterator it = std::begin(sequence);
    return *it;
}