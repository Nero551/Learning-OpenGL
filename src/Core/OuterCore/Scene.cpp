#include "Scene.hpp"

#include "Modules/Renderer/Components/CameraComponent.hpp"
#include "Modules/Renderer/Components/TransformComponent.hpp"
#include "World/Events/EntityDestroyed.hpp"


Entity& Scene::GetActiveCamera() {
    return *ActiveCamera;
}


void Scene::SetActiveCamera(Entity& entity) {
    if (entity.HasComponent<CameraComponent>() && entity.HasComponent<TransformComponent>()) {
        ActiveCamera = &entity;
    }
}

void Scene::SetRoot(Entity& entity) {
    Root = &entity;
}

Entity& Scene::GetRoot() {
    return *Root;
}
