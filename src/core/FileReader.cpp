#include <core/FileReader.hpp>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <filesystem>

std::string FileReader::read(const std::string& path) {
    namespace fs = std::filesystem;

    if (!fs::exists(path)) {
        throw std::runtime_error("File not found: " + path);
    }

    if (!fs::is_regular_file(path)) {
        throw std::runtime_error("Path is not a regular file: " + path);
    }

    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + path);
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}
