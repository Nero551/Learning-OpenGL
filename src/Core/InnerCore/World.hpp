#pragma once

#include "../OuterCore/Scene.hpp"
#include "Core/OuterCore/ServiceStore.hpp"
#include "Core/Services/EventBus.hpp"
#include "Utilities/Logger.hpp"
#include "World/Events/EntityCreated.hpp"

template <typename T>concept SceneType = std::derived_from<T, Scene>;

struct World {
    SafePtr<Scene> ActiveScene{"World Has No Active Scene"};

    template <SceneType T> T& CreateScene(const std::string& name) {
        auto scene = std::make_unique<T>();
        scene->Name = name;
        scene->Initialize();
        Scenes.emplace(name, std::move(scene));
        return GetScene<T>(name);
    }

    template <SceneType T> T& GetScene(const std::string& name) {
        auto scene = Scenes.find(name);
        if (scene == Scenes.end()) { Logger::Fatal("No Corresponding Scene."); }
        return static_cast<T&>(*scene->second);
    }

    void Start();

    void Update(double dt);

    void Stop();

    void BeginFrame(double dt);

    void EndFrame(double dt);

    void Render();

    template <EntityType T> T& CreateEntity() {
        const unsigned int id = ++currentEntityId;
        auto entity = std::make_unique<T>();
        entity->Id = id;
        entity->Initialize();

        ServiceStore::Ins->Get<EventBus>().Fire<EntityCreated>(*entity);

        Entities.emplace(id, std::move(entity));

        return static_cast<T&>(*Entities.find(id)->second);
    }

    Entity& FindEntity(unsigned int id);
    void RemoveEntity(unsigned int id);

private:
    std::unordered_map<std::string, std::unique_ptr<Scene>> Scenes;
    std::unordered_map<unsigned int, std::unique_ptr<Entity>> Entities;
    unsigned int currentEntityId = 0;
};
