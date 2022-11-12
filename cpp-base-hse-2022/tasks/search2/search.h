#pragma once

#include <string_view>
#include <vector>
#include <string>
#include <cmath>
#include <set>
#include <algorithm>

class Word {
private:
    size_t first_;
    size_t last_;
    int counter_ = 0;

public:
    Word(size_t start, size_t finish);
    size_t Len() const;
    size_t PosQuery(size_t s) const;
    int GetCounter() const;
    void IncreaseCounter();
};

class Line {
private:
    size_t first_;
    size_t last_;
    int count_words_ = 0;
    std::vector<std::pair<Word, int>> needed_words_;
    double tf_idf_ = 0.0;

public:
    Line(size_t start, size_t finish);
    void CountWords(std::string_view text);
    int CountInLine(std::string_view text, std::string_view query, Word& word);
    void TfIdf(size_t len);
    double GetTfIdf() const;
    bool operator<(const Line& other) const;
    bool operator==(const Line& other) const;
    void AppendWord(const Word& word, int num);
    std::string_view GetRes(std::string_view text) const;
};

class SearchEngine {
private:
    mutable std::vector<Line> lines_;
    std::string_view text_;

public:
    void BuildIndex(std::string_view text);
    std::vector<std::string_view> Search(std::string_view query, size_t results_count) const;
};
