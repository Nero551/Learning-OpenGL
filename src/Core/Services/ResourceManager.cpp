#include "ResourceManager.hpp"

namespace E {
    void ResourceManager::Destroy(const std::string& name) {
        if (Resources.contains(name)) {
            Resources.erase(name);
        }
    }
}