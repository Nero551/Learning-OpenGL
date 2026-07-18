#include "World.hpp"

#include "World/Events/EntityDestroyed.hpp"
#include "World/Scenes/FirstScene.hpp"

void World::Start() {
    auto& scene = CreateScene<FirstScene>("First Scene");
    ActiveScene = &scene;
}

void World::Update(double dt) {
    ActiveScene->Update(dt);
}

void World::FixedUpdate(double fdt) {
    ActiveScene->FixedUpdate(fdt);
}

void World::Render() {
    ActiveScene->Render();
}

void World::Stop() {
    ActiveScene->Stop();
}

void World::BeginFrame(double dt) {
    ActiveScene->BeginFrame(dt);
}

void World::EndFrame(double dt) {
    ActiveScene->EndFrame(dt);
}

void World::InternalRemoveEntity(unsigned int id) {
    if (Entities.contains(id)) {
        for (auto& scene : Scenes | std::views::values) {
            if (scene->IsRoot(id)) {
                Scenes.erase(scene->Name);
                break;
            }
        }

        ServiceStore::Ins->Get<EventBus>().Fire<EntityDestroyed>(FindEntity(id));
        Entities[id].release();
        Entities.erase(id);
    }
}

Entity& World::FindEntity(unsigned int id) {
    auto entity = Entities.find(id);
    if (entity == Entities.end()) {
        Logger::Fatal(std::format("Entity Not Found: {}", id));
    }
    return *entity->second;
}

CheckedPtr<Entity> World::TryFindEntity(unsigned int id) {
    auto entity = Entities.find(id);

    if (entity == Entities.end()) {
        return {};
    }

    return entity->second.get();
}

std::vector<CheckedPtr<Scene>> World::GetScenes() {
    std::vector<CheckedPtr<Scene>> scenes;
    scenes.reserve(Scenes.size());
    for (auto& scene : Scenes | std::views::values) {
        scenes.emplace_back(&*scene);
    }
    return scenes;
}

