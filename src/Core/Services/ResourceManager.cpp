#include "ResourceManager.hpp"

void ResourceManager::Destroy(const std::string& name) { if (Resources.contains(name)) { Resources.erase(name); } }
