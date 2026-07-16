#include "Scene.hpp"

#include "Modules/Renderer/Components/CameraComponent.hpp"
#include "Modules/Renderer/Components/Transform3DComponent.hpp"
#include "World/Events/EntityDestroyed.hpp"

Entity& Scene::GetActiveCamera() {
    return *ActiveCamera;
}

void Scene::SetActiveCamera(Entity& entity) {
    if (entity.HasComponent<CameraComponent>() && entity.HasComponent<Transform3DComponent>()) {
        ActiveCamera = &entity;
    }
}

void Scene::SetRoot(Entity& entity) {
    Root = &entity;
}

bool Scene::IsRoot(unsigned int id) {
    return !Root.IsNull() && Root->Id == id;
}

Entity& Scene::GetRoot() {
    return *Root;
}
