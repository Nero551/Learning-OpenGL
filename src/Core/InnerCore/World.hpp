#pragma once

#include "SystemOwner.hpp"
#include "../OuterCore/Scene.hpp"
#include "Core/OuterCore/Service.hpp"
#include "Core/Services/EventBus.hpp"
#include "Utilities/Logger.hpp"
#include "Utilities/Math/MathUtils.hpp"
#include "World/Events/EntityCreated.hpp"

namespace E {
template <typename T>concept EntityType = std::derived_from<T, Entity>;
template <typename T>concept SceneType = std::derived_from<T, Scene>;

struct World : SystemOwner {
    CheckedPtr<Entity> Root{"World Has No Root Entity"};
    CheckedPtr<Entity> ActiveCamera{"World Has No Active Camera"};
    int MaxLights = 64;

    static World& Get();

    void Start();

    void Update(double dt);

    void FixedUpdate(double fdt);

    void Stop();

    void BeginFrame(double dt);

    void EndFrame(double dt);

    void Render();

    template <SceneType T> T CreateScene() {
        return T();
    }

    template <EntityType T> T& CreateEntity() {
        const unsigned int id = ++currentEntityId;
        auto entity = std::make_unique<T>();
        entity->Id = id;
        entity->Initialize();

        Service::Get<EventBus>().Fire<EntityCreated>(*entity);

        Entities.emplace(id, std::move(entity));

        return static_cast<T&>(*Entities.find(id)->second);
    }

    Entity& FindEntity(unsigned int id);
    CheckedPtr<Entity> TryFindEntity(unsigned int id);

private:
    std::unordered_map<unsigned int, std::unique_ptr<Entity>> Entities;
    unsigned int currentEntityId = 0;

    void InternalRemoveEntity(unsigned int id);
    friend struct Entity;

protected:
    void AddSystems() override;
};
}
