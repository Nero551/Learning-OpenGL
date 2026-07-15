#pragma once

#include "Component.hpp"

#include "Utilities/Logger.hpp"
#include "Utilities/SafePtr.hpp"

struct Scene;
template <typename T>concept ComponentType = std::derived_from<T, Component>;

struct Entity {
    unsigned int Id = 0;

    virtual ~Entity() = default;

    Entity() = default;

    Entity(const Entity&) = delete;

    Entity& operator=(const Entity&) = delete;

    Entity(Entity&&) = default;

    Entity& operator=(Entity&&) = default;

    virtual void Initialize() {}

    template <ComponentType T> T& AddComponent() {
        if (Components.contains(typeid(T))) {
            Logger::Error(std::format("Entity {} already contains component {}", Id, typeid(T).name()));
            return static_cast<T&>((*Components.at(typeid(T))));
        }

        auto component = std::make_unique<T>();
        Components.emplace(typeid(T), std::move(component));
        return GetComponent<T>();
    }

    template <ComponentType T> T& GetComponent() const {
        auto component = Components.find(typeid(T));
        if (component == Components.end()) { Logger::Fatal(std::format("Component Not Found: {}", typeid(T).name())); }
        return static_cast<T&>((*component->second));
    }

    template <ComponentType T> bool HasComponent() const {
        auto component = Components.find(typeid(T));
        return component != Components.end();
    }

    template <ComponentType T> T& CopyComponent(T& otherComponent) {
        auto component = std::make_unique<T>(otherComponent);

        T& ref = *component;

        Components.insert_or_assign(typeid(T), std::move(component));

        return ref;
    }

    void AddChild(Entity& child);
    void AddChild(Scene& sceneChild);
    std::vector<SafePtr<Entity>> GetChildren();

private:
    std::unordered_map<std::type_index, std::unique_ptr<Component>> Components;
    std::unordered_map<unsigned int, SafePtr<Entity>> Children;
    SafePtr<Entity> Parent{"Scene Has No Parent"};
};
