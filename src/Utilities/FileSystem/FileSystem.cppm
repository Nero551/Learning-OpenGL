module;

#include <fstream>
#include <sstream>
#include <string>

export module FileSystem;

export namespace FileSystem {
std::string ReadFile(const std::string &path) {
    std::ifstream file(path);
    std::stringstream buffer;
    buffer << file.rdbuf();
    
    return buffer.str();
}
}
