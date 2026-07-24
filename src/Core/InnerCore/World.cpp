#include "World.hpp"

#include "World/Events/EntityDestroyed.hpp"
#include "World/Scenes/CalculusTesting.hpp"
#include "World/Scenes/CoordinateAxesScene.hpp"
#include "World/Scenes/FirstScene.hpp"
#include "World/Systems/TransformSystem.hpp"

void World::AddSystems() {
    AddSystem<TransformSystem>();
}

void World::Start() {
    AddSystems();

    auto& scene = CreateScene<CoordinateAxesScene>("Coordinate Axes");
    ActiveScene = &scene;

    auto& calculusTesting = CreateScene<CalculusTesting>("Calculus Testing");
    scene.GetRoot().AttachChild(calculusTesting.GetRoot());

    for (auto& system : Systems | std::views::values) {
        system->Start();
    }
}

void World::Update(double dt) {
    for (auto& scene : Scenes | std::views::values) {
        scene->Update(dt);
    }

    for (auto& system : Systems | std::views::values) {
        system->Update(dt);
    }
}

void World::FixedUpdate(double fdt) {
    for (auto& scene : Scenes | std::views::values) {
        scene->FixedUpdate(fdt);
    }
    for (auto& system : Systems | std::views::values) {
        system->FixedUpdate(fdt);
    }
}

void World::Render() {
    for (auto& scene : Scenes | std::views::values) {
        scene->Render();
    }
    for (auto& system : Systems | std::views::values) {
        system->Render();
    }
}

void World::Stop() {
    for (auto& scene : Scenes | std::views::values) {
        scene->Stop();
    }
    for (auto& system : Systems | std::views::values) {
        system->Stop();
    }
}

void World::BeginFrame(double dt) {
    for (auto& scene : Scenes | std::views::values) {
        scene->BeginFrame(dt);
    }
    for (auto& system : Systems | std::views::values) {
        system->BeginFrame(dt);
    }
}

void World::EndFrame(double dt) {
    for (auto& scene : Scenes | std::views::values) {
        scene->EndFrame(dt);
    }
    for (auto& system : Systems | std::views::values) {
        system->EndFrame(dt);
    }
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
