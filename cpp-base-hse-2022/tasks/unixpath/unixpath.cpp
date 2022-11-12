#include "unixpath.h"
#include <vector>

std::vector<std::string_view> Separate(std::string_view path) {
    std::vector<std::string_view> res;
    size_t start = 0;
    size_t finish = 0;
    for (size_t i = 0; i < path.size(); ++i) {
        if (path.at(i) == '/' && i == path.size() - 1) {
            if (i > 0) {
                res.push_back(path.substr(start, i - start));
            }
            res.push_back("/");
        } else if (path.at(i) == '/' && i < path.size() - 1) {
            finish = i;
            if (i > 0) {
                res.push_back(path.substr(start, finish - start));
            }
            start = i;
        } else if (path.at(i) != '/' && i == path.size() - 1) {
            finish = i + 1;
            if (i > 0) {
                res.push_back(path.substr(start, finish - start));
            }
            start = i;
        }
    }
    return res;
}

std::string NormalizePath(std::string_view current_working_dir, std::string_view path) {
    std::string res;
    if (path[0] == '/') {
        for (size_t i = 0; i < path.size(); ++i) {
            if (path[i] != '.' && !(!res.empty() && path[i] == '/' && res[res.size() - 1] == '/')) {
                res += path[i];
            }
        }
        if (res.size() > 1 && res[res.size() - 1] == '/') {
            res.erase(res.size() - 1, 1);
        }
        return res;
    }
    std::vector<std::string_view> abs_path = Separate(current_working_dir);
    std::vector<std::string_view> rel_path = Separate(path);
    int abs_pos = static_cast<int>(abs_path.size()) - 1;
    for (std::string_view str : rel_path) {
        if (str == ".." || str == "/..") {
            --abs_pos;
        } else if (str != "/." && str != "/" && str != ".") {
            if (abs_pos >= 0) {
                for (int i = 0; i <= abs_pos; ++i) {
                    res += abs_path[i];
                }
                abs_pos = -1;
            }
            res += str;
        }
    }
    if (res.empty()) {
        if (abs_pos < 0) {
            res = abs_path[0];
        } else {
            for (int i = 0; i <= abs_pos; ++i) {
                res += abs_path[i];
            }
        }
    }
    return res;
}