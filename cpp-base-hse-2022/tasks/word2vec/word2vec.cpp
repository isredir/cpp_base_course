#include "word2vec.h"

#include <vector>

int64_t ScalarProduct(const std::vector<int>& a, const std::vector<int>& b) {
    int64_t res = 0;
    for (size_t i = 0; i < a.size(); ++i) {
        res += static_cast<int64_t>(a[i]) * static_cast<int64_t>(b[i]);
    }
    return res;
}

std::vector<std::string> FindClosestWords(const std::vector<std::string>& words,
                                          const std::vector<std::vector<int>>& vectors) {
    std::vector<std::string> res = {};
    if (vectors.size() <= 1) {
        return res;
    }
    int64_t max_pr = ScalarProduct(vectors[0], vectors[1]);
    std::vector<int64_t> products;
    products.push_back(0);
    products.reserve(vectors.size());
    for (size_t i = 1; i < vectors.size(); ++i) {
        int64_t pr = ScalarProduct(vectors[i], vectors[0]);
        max_pr = std::max(max_pr, pr);
        products.push_back(pr);
    }
    for (size_t i = 1; i < vectors.size(); ++i) {
        if (products[i] == max_pr) {
            res.push_back(words[i]);
        }
    }
    return res;
}
