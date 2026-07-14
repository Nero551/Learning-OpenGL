#include "FileSystem.hpp"
#include <fstream>
#include <sstream>
#include <string>

#include "Utilities/Services/LoggerService.hpp"

std::string FileSystem::ReadFile(const std::string &path) {
   std::ifstream file(path);
   std::stringstream buffer;
   buffer << file.rdbuf();

   if (buffer.str() == "") {
      LoggerService::Error("File Doesn't Exist: " + path);
   }

   return buffer.str();
}
