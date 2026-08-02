#include "Scene.hpp"

#include "Modules/Renderer/Components/CameraComponent.hpp"
#include "World/Components/Transform3DComponent.hpp"
#include "World/Events/EntityDestroyed.hpp"

E::Entity& Scene::GetActiveCamera() {
    return *ActiveCamera;
}

void Scene::SetActiveCamera(E::Entity& entity) {
    if (entity.HasComponent<CameraComponent>() && entity.HasComponent<Transform3DComponent>()) {
        ActiveCamera = &entity;
    }
}

void Scene::SetRoot(E::Entity& entity) {
    Root = &entity;
}

bool Scene::IsRoot(unsigned int id) {
    return !Root.IsNull() && Root->Id == id;
}

E::Entity& Scene::GetRoot() {
    return *Root;
}
