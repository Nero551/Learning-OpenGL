#pragma once

#include "Component.hpp"

#include "Utilities/Logger.hpp"
#include "Utilities/CheckedPtr.hpp"


namespace E {
template <typename T>concept ComponentType = std::derived_from<T, Component>;

/**
 * @brief An entity is just a component container and id, entity can have children as well
 */
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
            return static_cast<T&>(*Components.at(typeid(T)));
        }

        auto component = std::make_unique<T>();
        Components.emplace(typeid(T), std::move(component));
        return GetComponent<T>();
    }

    template <ComponentType... Args> void AddComponents() {
        (..., AddComponent<Args>());
    }

    template <ComponentType T> T& GetComponent() const {
        auto component = Components.find(typeid(T));
        if (component == Components.end()) {
            Logger::Fatal(std::format("Component Not Found: {}", typeid(T).name()));
        }
        return static_cast<T&>(*component->second);
    }

    std::vector<CheckedPtr<Component>> GetAllComponents();

    template <ComponentType... Args> bool HasComponent() const {
        return (... && Components.contains(typeid(Args)));
    }

    void DestroyChild(unsigned int id);
    void AttachChild(Entity& child);
    void DetachChild(unsigned int id);
    Entity& GetChild(unsigned int id);
    CheckedPtr<Entity> TryGetChild(unsigned int id);
    bool HasChild(unsigned int id) const;

    size_t ChildCount() const;
    std::vector<CheckedPtr<Entity>> GetChildren();
    void DestroyChildren();

    std::vector<CheckedPtr<Entity>> GetDescendants();
    bool HasDescendant(unsigned int id) const;
    bool IsDescendantOf(const Entity& entity);

    std::vector<CheckedPtr<Entity>> GetAncestors();
    bool IsAncestorOf(const Entity& entity);
    bool HasAncestor(unsigned int id) const;

    Entity& GetParent();
    void SetParent(Entity& parent);
    void ClearParent();
    bool HasParent() const;

    void Destroy();
    Entity& GetRoot();

private:
    std::unordered_map<std::type_index, std::unique_ptr<Component>> Components;
    std::unordered_map<unsigned int, CheckedPtr<Entity>> Children;
    CheckedPtr<Entity> Parent{"Scene Has No Parent"};

    void RecursiveChildren(std::vector<CheckedPtr<Entity>>& entities, Entity& entity);
};
}
