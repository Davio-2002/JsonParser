#pragma once

#include <string>
#include <filesystem>

struct FileReader {
    static std::string read(const std::string& path);
};
