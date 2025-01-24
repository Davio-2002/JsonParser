#pragma once

#include <string>
#include <filesystem>

/**
 * @brief A class for reading files.
 * 
 * This class provides a static method to read the contents of a file
 * given its file path. The contents are returned as a string.
 */
struct FileReader {
    /**
     * @brief Reads the contents of a file.
     * 
     * @param path The path to the file to be read.
     * @return A string containing the contents of the file.
     * @throws std::runtime_error if the file cannot be opened or read.
     */
    static std::string read(const std::string& path);
};

struct FileReader {
    static std::string read(const std::string& path);
};
