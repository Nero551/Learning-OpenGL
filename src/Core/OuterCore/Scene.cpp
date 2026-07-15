#include "Scene.hpp"

#include <ranges>

#include "Modules/Renderer/Components/CameraComponent.hpp"
#include "Modules/Renderer/Components/TransformComponent.hpp"

void Scene::RemoveEntity(const unsigned int id) { Entities.erase(id); }

void Scene::SetActiveCamera(Entity& entity) {
    if (entity.HasComponent<CameraComponent>() && entity.HasComponent<TransformComponent>()) { ActiveCamera = &entity; }
}

void Scene::AddChild(Scene& childScene) {
    if (Children.contains(childScene.Name)) {
        LoggerService::Error("Child scene already exists: " + childScene.Name);
        return;
    }

    if (&childScene == this) {
        LoggerService::Error("A scene cannot be its own child.");
        return;
    }

    if (Parent.Get() == &childScene) {
        LoggerService::Error("A scene cannot have its parent as a child.");
        return;
    }

    SafePtr<Scene> childPtr = &childScene;
    Children.emplace(childScene.Name, std::move(childPtr));

    SafePtr<Scene> parentPtr = this;
    childScene.Parent = parentPtr;
}

void Scene::RemoveChild(const std::string& childName) {
    if (Children.contains(childName)) {
        Children.at(childName)->Parent.Reset();
        Children.erase(childName);
    }
    else { LoggerService::Error("Scene Doesn't Have Child Named: " + childName); }
}

std::vector<SafePtr<Entity>> Scene::GetEntities() {
    std::vector<SafePtr<Entity>> entities;
    entities.reserve(Entities.size());

    RecursiveEntities(entities);

    return entities;
}

std::vector<SafePtr<Scene>> Scene::GetChildren() {
    std::vector<SafePtr<Scene>> children;
    children.reserve(Children.size());

    for (auto& child : Children | std::views::values) {
        SafePtr<Scene> childPtr;
        childPtr = &*child;
        children.push_back(childPtr);
    }

    return children;
}

void Scene::RecursiveEntities(std::vector<SafePtr<Entity>>& entities) {
    for (auto& entity : Entities | std::views::values) {
        SafePtr<Entity> entityPtr;
        entityPtr = &*entity;
        entities.push_back(entityPtr);
    }

    for (auto& child : Children | std::views::values) { child->RecursiveEntities(entities); }
}
