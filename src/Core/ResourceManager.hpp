#pragma once

#include "Core/Module.hpp"
#include "Core/Resource.hpp"
#include <memory>
#include <unordered_map>

template <typename T>
concept ResourceType = std::derived_from<T, Resource>;

struct ResourceManager {
  std::unordered_map<std::string, std::unique_ptr<Resource>> Resources;

  template <ResourceType T, typename... Args> T &Load(const std::string &name, Args &&...args) {
    if (Resources.contains(name)) {
      return static_cast<T &>(*Resources.at(name));
    }

    auto resource = std::make_unique<T>(name, std::forward<Args>(args)...);
    T &ref = *resource;

    Resources.emplace(name, std::move(resource));

    return ref;
  }
};