#include "FileSystem.h"
#include <fstream>
#include <sstream>
#include <string>

std::string FileSystem::ReadFile(const std::string &path){
    std::ifstream file(path);
    std::stringstream buffer;
    buffer << file.rdbuf();
    
    return buffer.str();
}