#pragma once

#include "Entity.hpp"
#include "Utilities/SafePtr.hpp"

#include "ServiceStore.hpp"
#include "Modules/Renderer/Components/LightComponent.hpp"
#include "World/Events/EntityCreated.hpp"

template <typename T>concept EntityType = std::derived_from<T, Entity>;

struct Scene {
    std::string Name;
    const int MaxLights = 10;
    std::vector<SafePtr<Entity>> Lights;
    SafePtr<Entity> Root{"Scene Has No Root"};

    Scene() = default ;

    virtual ~Scene() = default;

    Scene(const Scene&) = delete;

    Scene& operator=(const Scene&) = delete;

    Scene(Scene&&) = default;


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

        ServiceStore::Ins->Get<EventBus>().Fire<EntityCreated>(*entity);

        Entities.emplace(id, std::move(entity));

        return static_cast<T&>(*Entities.find(id)->second);
    }


    Entity& GetEntity(unsigned int id);
    void RemoveEntity(unsigned int id);
    Entity& GetActiveCamera();
    void SetActiveCamera(Entity& entity);
    std::vector<SafePtr<Entity>> GetEntities();

private:
    SafePtr<Entity> ActiveCamera{"Scene Has No Active Camera Assigned"};
    std::unordered_map<unsigned int, std::unique_ptr<Entity>> Entities;
    unsigned int currentEntityId = 0;

    void RecursiveEntities(std::vector<SafePtr<Entity>>& entities, Entity& entity);
};
