#include "Entity.hpp"
#include "Scene.hpp"
#include "Core/InnerCore/Engine.hpp"

void Entity::AttachChild(Entity& child) {
    if (HasChild(child.Id)) {
        Logger::Error("Child Entity already exists: " + std::to_string(child.Id));
        return;
    }

    if (&child == this) {
        Logger::Error("An entity cannot be its own child.");
        return;
    }

    if (child.IsAncestorOf(*this)) {
        Logger::Error("An entity cannot have its ancestor as a child.");
        return;
    }

    if (child.Parent) {
        child.Parent->DetachChild(child.Id);
    }

    CheckedPtr<Entity> childPtr = &child;
    Children.emplace(child.Id, std::move(childPtr));

    child.Parent = this;
}

std::vector<CheckedPtr<Entity>> Entity::GetChildren() {
    std::vector<CheckedPtr<Entity>> children;
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


    auto descendants = child->second->GetDescendants();
    DetachChild(id);
    Engine::Ins->World.RemoveEntity(id);

    for (auto& descendant : descendants) {
        Engine::Ins->World.RemoveEntity(descendant->Id);
    }
}

std::vector<CheckedPtr<Entity>> Entity::GetDescendants() {
    std::vector<CheckedPtr<Entity>> descendants;
    descendants.reserve(Children.size());

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

void Entity::RecursiveChildren(std::vector<CheckedPtr<Entity>>& entities, Entity& entity) {
    for (auto& child : entity.Children | std::views::values) {
        CheckedPtr<Entity> entityPtr;
        entityPtr = &*child;
        entities.push_back(entityPtr);
        RecursiveChildren(entities, *entityPtr);
    }
}

Entity& Entity::GetParent() {
    return *Parent;
}

void Entity::SetParent(Entity& parent) {
    parent.AttachChild(*this);
}

void Entity::ClearParent() {
    if (HasParent()) {
        Parent->DetachChild(Id);
    }
}

bool Entity::HasParent() const {
    return !Parent.IsNull();
}

std::vector<CheckedPtr<Entity>> Entity::GetAncestors() {
    std::vector<CheckedPtr<Entity>> ancestors;

    auto current = Parent;

    while (current) {
        ancestors.push_back(current);
        current = current->Parent;
    }

    return ancestors;
}

bool Entity::IsDescendantOf(const Entity& entity) {
    return std::ranges::any_of(GetDescendants(), [&entity](const auto& descendant) {
        return descendant->Id == entity.Id;
    });
}

bool Entity::IsAncestorOf(const Entity& entity) {
    return std::ranges::any_of(GetAncestors(), [&entity](const auto& ancestor) {
        return ancestor->Id == entity.Id;
    });
}

Entity& Entity::GetRoot() {
    CheckedPtr<Entity> current = this;

    while (current->HasParent())
        current = current->Parent;

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
