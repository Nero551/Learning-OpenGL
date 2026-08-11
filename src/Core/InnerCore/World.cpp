#include "World.hpp"

#include "Engine.hpp"
#include "Modules/Input/Input.hpp"
#include "Modules/Input/Enums/Keys.hpp"
#include "World/Events/EntityDestroyed.hpp"
#include "World/experiments/calculus.hpp"
#include "World/Novas/Camera.hpp"
#include "World/Scenes/CoordinateAxesScene.hpp"
#include "World/Scenes/FirstScene.hpp"
#include "World/Systems/TransformSystem.hpp"

namespace E {
void World::AddSystems() {
    AddSystem<TransformSystem>();
    AddSystem<calculus>();
}

World& World::Get() {
    return Engine::Get().World;
}

void World::Start() {
    AddSystems();
    Root = &CreateEntity<Nova>();

    auto& camera = CreateEntity<Camera>();
    Root->AttachChild(camera);
    ActiveCamera = &camera;

    auto coordinateAxes = CreateScene<CoordinateAxesScene>();
    Root->AttachChild(*coordinateAxes.Root);

    for (auto& system : Systems | std::views::values) {
        system->Start();
    }
    //
}

void World::Update(double dt) {
    for (auto& system : Systems | std::views::values) {
        system->Update(dt);
    }
}

void World::FixedUpdate(double fdt) {
    for (auto& system : Systems | std::views::values) {
        system->FixedUpdate(fdt);
    }
}

void World::Render() {
    for (auto& system : Systems | std::views::values) {
        system->Render();
    }
}

void World::Stop() {
    for (auto& system : Systems | std::views::values) {
        system->Stop();
    }
}

void World::BeginFrame(double dt) {
    for (auto& system : Systems | std::views::values) {
        system->BeginFrame(dt);
    }
}

void World::EndFrame(double dt) {
    for (auto& system : Systems | std::views::values) {
        system->EndFrame(dt);
    }
}

void World::InternalRemoveEntity(unsigned int id) {
    if (Entities.contains(id)) {
        Service::Get<EventBus>().Fire<EntityDestroyed>(FindEntity(id));
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
        return nullptr;
    }

    return entity->second.get();
}
}
