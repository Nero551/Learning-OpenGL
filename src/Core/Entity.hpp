#pragma once

#include "Component.hpp"
#include <concepts>
#include <memory>
#include <format>
#include <ranges>
#include <typeindex>
#include <unordered_map>

template<typename T>concept ComponentType = std::derived_from<T, Component>;

struct Entity {
   unsigned int Id = 0;

   virtual ~Entity() {}

   Entity() = default;

   Entity(const Entity &) = delete;

   Entity &operator=(const Entity &) = delete;

   Entity(Entity &&) = default;

   Entity &operator=(Entity &&) = default;

   virtual void Initialize() {}

   template<ComponentType T> T &AddComponent() {
      auto component = std::make_unique<T>();

      T &ref = *component;

      Components.emplace(typeid(T), std::move(component));
      return ref;
   }

   template<ComponentType T> T &GetComponent() {
      auto component = Components.find(typeid(T));
      if (component == Components.end()) {
         throw std::runtime_error(std::format("Component Not Found: {}", typeid(T).name()));
      }
      return static_cast<T &>((*component->second));
   }

   template<ComponentType T> bool HasComponent() {
      auto component = Components.find(typeid(T));
      return component != Components.end();
   }

   // template<ComponentType T> T &CopyComponent(const T &otherComponent) {
   //    auto component = std::make_unique<T>(otherComponent);
   //
   //    T *ptr = component.get();
   //
   //    Components.insert_or_assign(typeid(T), std::move(component));
   //
   //    return *ptr;
   // }

private:
   std::unordered_map<std::type_index, std::unique_ptr<Component> > Components;
};
