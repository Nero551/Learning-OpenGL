#include "FileSystem.hpp"
#include <fstream>
#include <sstream>

#include "Utilities/Logger.hpp"

std::string FileSystem::ReadFile(const std::string& path) {
    std::ifstream file(path);
    std::stringstream buffer;
    buffer << file.rdbuf();

    if (buffer.str() == "") { Logger::Error("File Doesn't Exist: " + path); }

    return buffer.str();
}
