#pragma once
namespace E::U::FileSystem {
std::string ReadFile(const std::string& path);
void WriteFile(const std::string& path, const std::string& content);
}
