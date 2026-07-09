#pragma once
#include "Component.hpp"
#include <concepts>
#include <typeindex>
#include <unordered_map>

template <typename T>
concept ComponentType = std::derived_from<T, Component>;

struct Entity {
  unsigned int Id;
  Entity(const unsigned int id) : Id(id) { Entity::Initialize(); }

  template <ComponentType T> T &AddComponent() {
    T component;
    Components.insert({std::type_index(typeid(T)), component});
    return Components.at(component);
  }

  template <ComponentType T> T &GetComponent() {
    auto component = Components.find(std::type_index(typeid(T)));

    if (component != Components.end()) {
      return component->second;
    }
    return NULL;
  }

  template <ComponentType T> bool HasComponent() {
    auto component = Components.find(std::type_index(typeid(T)));
    if (component != Components.end()) {
      return true;
    }
    return false;
  }

protected:
  virtual void Initialize();

private:
  std::unordered_map<std::type_index, Component> Components;
};