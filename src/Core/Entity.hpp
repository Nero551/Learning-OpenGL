#pragma once

#include "Component.hpp"
#include <concepts>
#include <memory>
#include <vector>
#include <typeindex>
#include <unordered_map>

template <typename T>
concept ComponentType = std::derived_from<T, Component>;

struct Entity {
  unsigned int Id = 0;

  virtual ~Entity() {}

  virtual void Initialize() {}

  // TODO- rework how components are stored

  template <ComponentType T> T &AddComponent() {
    auto component = std::make_unique<T>();

    T &ref = *component;

    Components.push_back(std::move(component));
    return ref;
  }

private:
  std::vector<std::unique_ptr<Component>> Components;
};