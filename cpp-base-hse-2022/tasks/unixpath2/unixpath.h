#pragma once

#include <string>
#include <string_view>
#include <vector>

class UnixPath {
public:
    UnixPath(std::string_view initial_dir);

    void ChangeDirectory(std::string_view path);

    std::string GetAbsolutePath() const;
    std::string GetRelativePath() const;

private:
    std::vector<std::string> Normalise(const std::vector<std::string>& path);
    static std::vector<std::string> Separate(std::string_view path);
    std::vector<std::string> original_path_;
    std::vector<std::string> dynamic_path_;
};
