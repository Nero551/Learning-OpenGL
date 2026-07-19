#pragma once

#include "SystemOwner.hpp"
#include "../OuterCore/Scene.hpp"
#include "Core/OuterCore/ServiceStore.hpp"
#include "Core/Services/EventBus.hpp"
#include "Utilities/Logger.hpp"
#include "World/Events/EntityCreated.hpp"
template <typename T>concept EntityType = std::derived_from<T, Entity>;
template <typename T>concept SceneType = std::derived_from<T, Scene>;

struct World : SystemOwner {
    CheckedPtr<Scene> ActiveScene{"World Has No Active Scene"};

    void Start();

    void Update(double dt);

    void FixedUpdate(double fdt);

    void Stop();

    void BeginFrame(double dt);

    void EndFrame(double dt);

    void Render();

    template <SceneType T, typename... Args> T& CreateScene(const std::string& name, Args... args) {
        if (Scenes.contains(name)) {
            Logger::Error("Scene: ", name, " already exists.");
            return static_cast<T&>(*Scenes.at(name));
        }

        auto scene = std::make_unique<T>(std::forward<Args>(args)...);
        scene->Name = name;

        T& ref = *scene;

        Scenes.emplace(name, std::move(scene));

        return ref;
    }

    template <SceneType T> T& GetScene(const std::string& name) {
        auto scene = Scenes.find(name);
        if (scene == Scenes.end()) {
            Logger::Fatal("No Corresponding Scene.");
        }
        return static_cast<T&>(*scene->second);
    }

    std::vector<CheckedPtr<Scene>> GetScenes();

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
    CheckedPtr<Entity> TryFindEntity(unsigned int id);

private:
    std::unordered_map<std::string, std::unique_ptr<Scene>> Scenes;
    std::unordered_map<unsigned int, std::unique_ptr<Entity>> Entities;
    unsigned int currentEntityId = 0;
    void InternalRemoveEntity(unsigned int id);

    friend struct Entity;

protected:
    void AddSystems() override;
};
