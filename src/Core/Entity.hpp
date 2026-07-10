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

    Components.emplace(typeid(T), std::move(component));
    return ref;
  }

  template <ComponentType T> T &GetComponent() {
    auto component = Components.find(typeid(T));
    if (component == Components.end()) {
      throw std::runtime_error("No corresponding component");
    }
    return static_cast<T &>((*component->second));
  }

  template <ComponentType T> bool HasComponent() {
    auto component = Components.find(typeid(T));
    return component != Components.end();
  }

private:
  std::unordered_map<std::type_index, std::unique_ptr<Component>> Components;
};