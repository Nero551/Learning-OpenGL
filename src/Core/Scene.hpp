#pragma once

#include "Entity.hpp"
#include "Utilities/SafePtr.hpp"
#include <unordered_map>
#include <format>
#include <vector>

#include "Modules/Renderer/Components/LightComponent.hpp"

template <typename T>concept EntityType = std::derived_from<T, Entity>;

struct Scene {
    std::string Name;
    const int MaxLights = 10;
    std::vector<SafePtr<Entity>> Lights;

    Scene() = default ;

    virtual ~Scene() = default;

    Scene(const Scene&) = delete;

    Scene& operator=(const Scene&) = delete;

    Scene(Scene&&) = default;

    Scene& operator=(Scene&&) = default;

    virtual void Initialize() {}

    virtual void Update(double dt) {}

    virtual void Render() {}

    virtual void BeginFrame(double dt) {}

    virtual void EndFrame(double dt) {}

    virtual void Stop() {}

    template <EntityType T> T& CreateEntity() {
        const unsigned int id = ++currentEntityId;
        auto entity = std::make_unique<T>();
        entity->Id = id;
        entity->Initialize();

        if (entity->template HasComponent<LightComponent>() && Lights.size() < MaxLights) {
            SafePtr<Entity> lightPtr = entity.get();
            Lights.emplace_back(lightPtr);
        }

        Entities.emplace(id, std::move(entity));

        return GetEntity<T>(id);
    }

    template <EntityType T> T& GetEntity(unsigned int id) {
        auto entity = Entities.find(id);
        if (entity == Entities.end()) { LoggerService::Fatal(std::format("Entity Not Found: {}", typeid(T).name())); }
        return static_cast<T&>((*entity->second));
    }

    template <EntityType T> T& GetActiveCamera() { return static_cast<T&>(*ActiveCamera); }

    void SetActiveCamera(Entity& entity);
    void AddChild(Scene& childScene);
    void RemoveChild(const std::string& childName);
    std::vector<SafePtr<Entity>> GetEntities();
    std::vector<SafePtr<Scene>> GetChildren();

private:
    SafePtr<Entity> ActiveCamera{"Scene Has No Active Camera Assigned"};
    std::unordered_map<unsigned int, std::unique_ptr<Entity>> Entities;
    SafePtr<Scene> Parent{"Scene Has No Parent"};
    std::unordered_map<std::string, SafePtr<Scene>> Children;
    unsigned int currentEntityId = 0;

    void RecursiveEntities(std::vector<SafePtr<Entity>>& entities);
};
