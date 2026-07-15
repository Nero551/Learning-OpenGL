#include "Scene.hpp"

#include "Modules/Renderer/Components/CameraComponent.hpp"
#include "Modules/Renderer/Components/TransformComponent.hpp"
#include "World/Events/EntityDestroyed.hpp"

Entity& Scene::GetEntity(unsigned int id) {
    auto entity = Entities.find(id);
    if (entity == Entities.end()) { Logger::Fatal(std::format("Entity Not Found: {}", id)); }
    return (*entity->second);
}

Entity& Scene::GetActiveCamera() { return *ActiveCamera; }

void Scene::RemoveEntity(unsigned int id) {
    if (Entities.contains(id)) {
        ServiceStore::Ins->Get<EventBus>().Fire<EntityDestroyed>(GetEntity(id));
        Entities.erase(id);
    }
    Root->RemoveChild(id);
    for (auto& child : Root->GetChildren()) { child->RemoveChild(id); }
}

void Scene::SetActiveCamera(Entity& entity) {
    if (entity.HasComponent<CameraComponent>() && entity.HasComponent<TransformComponent>()) { ActiveCamera = &entity; }
}

std::vector<SafePtr<Entity>> Scene::GetEntities() {
    std::vector<SafePtr<Entity>> entities;
    RecursiveEntities(entities, *Root);
    return entities;
}


void Scene::RecursiveEntities(std::vector<SafePtr<Entity>>& entities, Entity& entity) {
    for (auto& child : entity.GetChildren()) {
        SafePtr<Entity> entityPtr;
        entityPtr = &*child;
        entities.push_back(entityPtr);
        RecursiveEntities(entities, *entityPtr);
    }
}
