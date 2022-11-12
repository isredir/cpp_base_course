#pragma once

#include <forward_list>
#include <string>

using Value = std::string;
using Iterator = std::forward_list<std::string>::const_iterator;
using ZippedPair = std::pair<const Value&, const Value&>;

class Zipped {
public:
    class ZipIter {
    public:
        ZipIter(Iterator it1, Iterator it2, Iterator end1, Iterator end2);
        ZipIter& operator++();
        bool operator==(const ZipIter& other) const;
        bool operator!=(const ZipIter& other) const;
        ZippedPair operator*();

    private:
        Iterator first_;
        Iterator second_;
        Iterator first_end_;
        Iterator second_end_;
    };
    Zipped(Iterator a_begin, Iterator a_end, Iterator b_begin, Iterator b_end);
    ZipIter begin() const;  // NOLINT
    ZipIter end() const;    // NOLINT
private:
    ZipIter begin_;
    ZipIter end_;
};

Zipped Zip(Iterator a_begin, Iterator a_end, Iterator b_begin, Iterator b_end);
