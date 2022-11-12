#include "unixpath.h"

std::vector<std::string> UnixPath::Separate(std::string_view path) {
    std::string str{path};
    std::vector<std::string> res;
    size_t start = 0;
    size_t finish = 0;
    for (size_t i = 0; i < str.size(); ++i) {
        char pos = str.at(i);
        if (pos == '/' && i == str.size() - 1) {
            if (i > 0) {
                res.push_back(str.substr(start, i - start));
            }
            res.push_back("/");
        } else if (pos == '/' && i < str.size() - 1) {
            finish = i;
            if (i > 0) {
                res.push_back(str.substr(start, finish - start));
            }
            start = i;
        } else if (pos != '/' && i == str.size() - 1) {
            finish = i + 1;
            if (i > 0) {
                res.push_back(str.substr(start, finish - start));
            }
            start = i;
        }
    }
    return res;
}

std::vector<std::string> UnixPath::Normalise(const std::vector<std::string>& path) {
    std::vector<std::string> res_normalised;
    for (const std::string& str : path) {
        if (!res_normalised.empty() && (str == "/.." || str == "..") && res_normalised.back() != "/..") {
            res_normalised.pop_back();
        } else if (str != "." && str != "/." && str != "/") {
            res_normalised.push_back(str);
        }
    }
    return res_normalised;
}

UnixPath::UnixPath(std::string_view initial_dir) {
    original_path_ = Normalise(Separate(initial_dir));
    dynamic_path_ = Normalise(Separate(initial_dir));
}

void UnixPath::ChangeDirectory(std::string_view path) {
    std::vector<std::string> new_path = Normalise(Separate(path));
    if (!path.empty() && path[0] == '/') {
        dynamic_path_ = new_path;
    } else {
        for (const std::string& str : new_path) {
            dynamic_path_.push_back(str);
        }
        dynamic_path_ = Normalise(dynamic_path_);
    }
}

std::string UnixPath::GetAbsolutePath() const {
    std::string res;
    for (const std::string& str : dynamic_path_) {
        if (str != "/..") {
            res += str;
        }
    }
    return res;
}

std::string UnixPath::GetRelativePath() const {
    std::string res;
    if (dynamic_path_[0] != original_path_[0]) {
        res += "..";
        for (const std::string& str : dynamic_path_) {
            res += str;
        }
        return res;
    }
    size_t level = 0;
    for (size_t i = 0; i < dynamic_path_.size(); ++i) {
        if (i < original_path_.size() && dynamic_path_[i] == original_path_[i]) {
            ++level;
        } else {
            break;
        }
    }
    if (level == original_path_.size()) {
        res += '.';
        for (size_t i = level; i < dynamic_path_.size(); ++i) {
            res += dynamic_path_[i];
        }
        return res;
    }
    res += "..";
    for (size_t i = 0; i < level - 1; ++i) {
        res += "/..";
    }
    for (size_t i = level; i < dynamic_path_.size(); ++i) {
        res += dynamic_path_[i];
    }
    return res;
}
