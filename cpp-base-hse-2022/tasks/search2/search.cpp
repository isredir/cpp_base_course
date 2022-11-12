#include "search.h"

Word::Word(size_t start, size_t finish) {
    this->first_ = start;
    this->last_ = finish;
}

size_t Word::Len() const {
    return last_ - first_;
}

size_t Word::PosQuery(size_t s) const {
    return first_ + s;
}

int Word::GetCounter() const {
    return counter_;
}

void Word::IncreaseCounter() {
    ++counter_;
}

Line::Line(size_t start, size_t finish) {
    this->first_ = start;
    this->last_ = finish;
}
void Line::CountWords(std::string_view text) {
    int count = 0;
    size_t start = 0;
    size_t finish = 0;
    for (size_t i = first_; i <= last_; ++i) {
        if (!std::isalpha(text[i]) || i == last_) {
            if (i == last_ && std::isalpha(text[i])) {
                ++i;
            }
            finish = i;
            if (start != finish) {
                ++count;
            }
            start = i + 1;
        }
    }
    count_words_ = count;
}

int Line::CountInLine(std::string_view text, std::string_view query, Word& word) {
    int count = 0;
    for (size_t i = first_; i + word.Len() <= last_; ++i) {
        bool found = true;
        size_t j = i;
        if (j > first_ && std::isalpha(text[j - 1])) {
            found = false;
        }
        for (; j <= i + word.Len(); ++j) {
            if (tolower(text[j]) != tolower(query[word.PosQuery(j - i)])) {
                found = false;
                break;
            }
        }
        if (j <= last_ && std::isalpha(text[j])) {
            found = false;
        }
        if (found) {
            ++count;
        }
    }
    return count;
}

void Line::TfIdf(size_t len) {
    double sum = 0.0;
    for (const auto& [word, counter] : needed_words_) {
        sum += (static_cast<double>(counter) / count_words_) * log(static_cast<double>(len) / word.GetCounter());
    }
    tf_idf_ = sum;
}

double Line::GetTfIdf() const {
    return tf_idf_;
}

bool Line::operator<(const Line& other) const {
    return this->tf_idf_ < other.tf_idf_;
}
bool Line::operator==(const Line& other) const {
    return this->tf_idf_ == other.tf_idf_;
}

void Line::AppendWord(const Word& word, int num) {
    needed_words_.push_back(std::make_pair(word, num));
}

std::string_view Line::GetRes(std::string_view text) const {
    return text.substr(first_, last_ - first_ + 1);
}

void SearchEngine::BuildIndex(std::string_view text) {
    text_ = text;
    size_t start = 0;
    size_t finish = 0;
    for (size_t i = 0; i < text.size(); ++i) {
        if (text[i] == '\n' || i == text.size() - 1) {
            if (i == text.size() - 1) {
                ++i;
            }
            finish = i;
            Line line = {start, finish - 1};
            line.CountWords(text);
            lines_.push_back(line);
            start = i + 1;
        }
    }
}

std::vector<std::string_view> SearchEngine::Search(std::string_view query, size_t results_count) const {
    std::vector<Word> query_count;
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
                Word word = {start, finish - 1};
                query_count.push_back(word);
            }
            start = i + 1;
        }
    }
    for (Word& word : query_count) {
        for (Line& line : lines_) {
            int num = line.CountInLine(text_, query, word);
            if (num > 0) {
                word.IncreaseCounter();
            }
        }
    }
    for (Word& word : query_count) {
        for (Line& line : lines_) {
            int num = line.CountInLine(text_, query, word);
            if (num > 0) {
                line.AppendWord(word, num);
            }
        }
    }
    for (Line& line : lines_) {
        line.TfIdf(lines_.size());
    }
    std::stable_sort(lines_.rbegin(), lines_.rend());
    std::vector<std::string_view> res;
    for (const Line& line : lines_) {
        if (res.size() == results_count || line.GetTfIdf() <= 0) {
            break;
        }
        res.push_back(line.GetRes(text_));
    }
    return res;
}
