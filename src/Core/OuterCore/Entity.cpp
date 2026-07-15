#include "Entity.hpp"
#include "Scene.hpp"

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

    SafePtr<Entity> childPtr = &child;
    Children.emplace(child.Id, std::move(childPtr));

    child.Parent = this;
}

void Entity::AddChild(Scene& childScene) { AddChild(*childScene.Root); }

std::vector<SafePtr<Entity>> Entity::GetChildren() {
    std::vector<SafePtr<Entity>> children;
    children.reserve(Children.size());

    for (auto& child : Children | std::views::values) { children.emplace_back(child); }

    return children;
}
