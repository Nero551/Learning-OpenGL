#pragma once

#include "Core/Resource.hpp"
#include <memory>
#include <unordered_map>

template <typename T>concept ResourceType = std::derived_from<T, Resource>;

struct ResourceManager
{
    template <ResourceType T, typename... Args> T& Load(const std::string& name, Args&&... args)
    {
        if (Resources.contains(name)) { return static_cast<T&>(*Resources.at(name)); }

        auto resource = std::make_unique<T>(name, std::forward<Args>(args)...);
        Resources.emplace(name, std::move(resource));

        return static_cast<T&>(*Resources.at(name));
    }

    void Destroy(const std::string& name) { if (Resources.contains(name)) { Resources.erase(name); } }

    ResourceManager() = default;

    ResourceManager(const ResourceManager&) = delete;

    ResourceManager& operator=(const ResourceManager&) = delete;

private:
    std::unordered_map<std::string, std::unique_ptr<Resource>> Resources;
};
