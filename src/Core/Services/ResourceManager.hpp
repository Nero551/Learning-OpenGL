#pragma once

#include "Core/OuterCore/Resource.hpp"
#include "Core/OuterCore/Service.hpp"
#include "Utilities/Logger.hpp"

template <typename T>concept ResourceType = std::derived_from<T, Resource>;

struct ResourceManager : Service {
    template <ResourceType T, typename... Args> T& Load(const std::string& name, Args&&... args) {
        if (Resources.contains(name)) {
            Logger::Warning("Resource: " + name + " Already Loaded.");
            return static_cast<T&>(*Resources.at(name));
        }

        auto resource = std::make_unique<T>(name, std::forward<Args>(args)...);
        Resources.emplace(name, std::move(resource));

        return static_cast<T&>(*Resources.at(name));
    }

    void Destroy(const std::string& name);

    ResourceManager() = default;

    ResourceManager(const ResourceManager&) = delete;

    ResourceManager& operator=(const ResourceManager&) = delete;

private:
    std::unordered_map<std::string, std::unique_ptr<Resource>> Resources;
};
