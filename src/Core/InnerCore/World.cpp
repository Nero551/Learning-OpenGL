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

void World::RemoveEntity(unsigned int id) {
    if (Entities.contains(id)) {
        ServiceStore::Ins->Get<EventBus>().Fire<EntityDestroyed>(FindEntity(id));
        Entities.erase(id);
    }
}

Entity& World::FindEntity(unsigned int id) {
    auto entity = Entities.find(id);
    if (entity == Entities.end()) {
        Logger::Fatal(std::format("Entity Not Found: {}", id));
    }
    return (*entity->second);
}
