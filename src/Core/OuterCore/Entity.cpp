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

    if (child.IsAncestorOf(*this)) {
        Logger::Error("An entity cannot have its ancestor as a child.");
        return;
    }

    if (child.Parent) {
        child.Parent->DetachChild(child.Id);
    }

    SafePtr<Entity> childPtr = &child;
    Children.emplace(child.Id, std::move(childPtr));

    child.Parent = this;
}

std::vector<SafePtr<Entity>> Entity::GetChildren() {
    std::vector<SafePtr<Entity>> children;
    children.reserve(Children.size());

    for (auto& child : Children | std::views::values) {
        children.emplace_back(child);
    }

    return children;
}

void Entity::DestroyChild(unsigned int id) {
    auto child = Children.find(id);
    if (child == Children.end()) {
        return;
    }

    for (auto& descendant : child->second->GetDescendants()) {
        Engine::Ins->World.RemoveEntity(descendant->Id);
    }


    DetachChild(id);
    Engine::Ins->World.RemoveEntity(id);
}

std::vector<SafePtr<Entity>> Entity::GetDescendants() {
    std::vector<SafePtr<Entity>> descendants;

    RecursiveChildren(descendants, *this);

    return descendants;
}

void Entity::DetachChild(unsigned int id) {
    auto child = Children.find(id);

    if (child != Children.end()) {
        child->second->Parent.Reset();
        Children.erase(child);
    }
}

void Entity::RecursiveChildren(std::vector<SafePtr<Entity>>& entities, Entity& entity) {
    for (auto& child : entity.Children | std::views::values) {
        SafePtr<Entity> entityPtr;
        entityPtr = &*child;
        entities.push_back(entityPtr);
        RecursiveChildren(entities, *entityPtr);
    }
}

Entity& Entity::GetParent() {
    return *Parent;
}

std::vector<SafePtr<Entity>> Entity::GetAncestors() {
    std::vector<SafePtr<Entity>> ancestors;

    auto current = Parent;

    while (current) {
        ancestors.push_back(current);
        current = current->Parent;
    }

    return ancestors;
}

bool Entity::IsDescendantOf(const Entity& entity) {
    for (auto& descendant : GetDescendants()) {
        if (descendant->Id == entity.Id) {
            return true;
        }
    }
    return false;
}

bool Entity::IsAncestorOf(const Entity& entity) {
    for (auto& ancestor : GetAncestors()) {
        if (ancestor->Id == entity.Id) {
            return true;
        }
    }
    return false;
}

Entity& Entity::GetRoot() {
    SafePtr<Entity> current = this;

    while (current->Parent)
        current = current->Parent.Get();

    return *current;
}

bool Entity::HasChild(unsigned int id) const {
    return Children.contains(id);
}

Entity& Entity::GetChild(unsigned int id) {
    auto child = Children.find(id);

    if (child != Children.end()) {
        return *child->second;
    }

    Logger::Fatal(std::format("Entity {} has no child {}", Id, id));
}

size_t Entity::ChildCount() const {
    return Children.size();
}
