#include "ResourceManager.hpp"

namespace E {
void ResourceManager::Unload(const std::string& name) {
    if (Resources.contains(name)) {
        Resources.erase(name);
    }
}
}
