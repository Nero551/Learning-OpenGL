#include "Entity.hpp"
#include "Scene.hpp"
#include "Core/InnerCore/Engine.hpp"

void Entity::AddChild(Entity& child) {
    if (Children.contains(child.Id)) {
        Logger::Error("Child Entity already exists: " + std::to_string(child.Id));
        return;
    }

    if (&child == this) {
        Logger::Error("An entity cannot be its own child.");
        return;
    }

    if (Parent.Get() == &child) {
        Logger::Error("An entity cannot have its parent as a child.");
        return;
    }

    if (child.Parent) {
        child.Parent->RemoveChild(child.Id);
    }


    SafePtr<Entity> childPtr = &child;
    Children.emplace(child.Id, std::move(childPtr));

    child.Parent = this;
}

void Entity::AddChild(Scene& childScene) {
    AddChild(*childScene.Root);
}

std::vector<SafePtr<Entity>> Entity::GetChildren() {
    std::vector<SafePtr<Entity>> children;
    children.reserve(Children.size());

    for (auto& child : Children | std::views::values) {
        children.emplace_back(child);
    }

    return children;
}

void Entity::RemoveChild(unsigned int id) {
    auto child = Children.find(id);
    if (child == Children.end()) {
        return;
    }

    std::vector<SafePtr<Entity>> toDelete;
    RecursiveChildren(toDelete, *child->second);

    toDelete.emplace_back(child->second);

    Children.erase(child);

    for (auto& entity : toDelete) {
        Engine::Ins->World.RemoveEntity(entity->Id);
    }
}

std::vector<SafePtr<Entity>> Entity::GetDescendants() {
    std::vector<SafePtr<Entity>> descendants;

    RecursiveChildren(descendants, *this);

    return descendants;
}

void Entity::RecursiveChildren(std::vector<SafePtr<Entity>>& entities, Entity& entity) {
    for (auto& child : entity.Children | std::views::values) {
        SafePtr<Entity> entityPtr;
        entityPtr = &*child;
        entities.push_back(entityPtr);
        RecursiveChildren(entities, *entityPtr);
    }
}
