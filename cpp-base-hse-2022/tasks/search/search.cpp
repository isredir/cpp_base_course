#include "search.h"
#include <string_view>
#include <vector>
#include <string>
#include <cmath>
#include <set>

struct Word {
    size_t first;
    size_t last;
    int counter = 0;
};

struct Line {
    size_t first;
    size_t last;
    int count_words = 0;
    std::vector<std::pair<Word, int>> needed_words;
    double tf_idf = 0.0;
};

int CountWords(std::string_view text, Line& line) {
    int count = 0;
    size_t start = 0;
    size_t finish = 0;
    for (size_t i = line.first; i <= line.last; ++i) {
        if (!std::isalpha(text[i]) || i == line.last) {
            if (i == line.last && std::isalpha(text[i])) {
                ++i;
            }
            finish = i;
            if (start != finish) {
                ++count;
            }
            start = i + 1;
        }
    }
    line.count_words = count;
    return count;
}

int CountInLine(std::string_view text, std::string_view query, Word& word, Line& line) {
    int count = 0;
    for (size_t i = line.first; i + (word.last - word.first) <= line.last; ++i) {
        bool found = true;
        size_t j = i;
        if (j > line.first && std::isalpha(text[j - 1])) {
            found = false;
        }
        for (; j <= i + (word.last - word.first); ++j) {
            if (tolower(text[j]) != tolower(query[word.first + (j - i)])) {
                found = false;
                break;
            }
        }
        if (j <= line.last && std::isalpha(text[j])) {
            found = false;
        }
        if (found) {
            ++count;
        }
    }
    return count;
}

double TfIdf(Line& line, size_t len) {
    double sum = 0.0;
    for (const auto& [word, counter] : line.needed_words) {
        sum += (static_cast<double>(counter) / line.count_words) * log(static_cast<double>(len) / word.counter);
    }
    line.tf_idf = sum;
    return sum;
}

bool CmpLines(const Line& a, const Line& b) {
    return a.tf_idf > b.tf_idf;
}

std::vector<std::string_view> Search(std::string_view text, std::string_view query, size_t results_count) {
    std::vector<Word> query_count;
    std::vector<Line> lines;
    std::set<std::string_view> words;
    size_t start = 0;
    size_t finish = 0;
    for (size_t i = 0; i < query.size(); ++i) {
        if (!std::isalpha(query[i]) || i == query.size() - 1) {
            if (i == query.size() - 1 && std::isalpha(query[i])) {
                ++i;
            }
            finish = i;
            if (start != finish && words.find(query.substr(start, finish - start)) == words.end()) {
                words.insert(query.substr(start, finish - start));
                query_count.push_back({start, finish - 1, 0});
            }
            start = i + 1;
        }
    }
    start = 0;
    finish = 0;
    for (size_t i = 0; i < text.size(); ++i) {
        if (text[i] == '\n' || i == text.size() - 1) {
            if (i == text.size() - 1) {
                ++i;
            }
            finish = i;
            Line line = {start, finish - 1};
            CountWords(text, line);
            lines.push_back(line);
            start = i + 1;
        }
    }
    for (Word& word : query_count) {
        for (Line& line : lines) {
            int num = CountInLine(text, query, word, line);
            if (num > 0) {
                ++word.counter;
            }
        }
    }
    for (Word& word : query_count) {
        for (Line& line : lines) {
            int num = CountInLine(text, query, word, line);
            if (num > 0) {
                line.needed_words.push_back(std::make_pair(word, num));
            }
        }
    }
    for (Line& line : lines) {
        TfIdf(line, lines.size());
    }
    std::stable_sort(lines.begin(), lines.end(), CmpLines);
    std::vector<std::string_view> res;
    for (const Line& line : lines) {
        if (res.size() == results_count || line.tf_idf <= 0) {
            break;
        }
        res.push_back(text.substr(line.first, line.last - line.first + 1));
    }
    return res;
}
