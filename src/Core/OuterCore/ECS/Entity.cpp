#include "Entity.hpp"

#include "../Scene.hpp"
#include "Core/InnerCore/Engine.hpp"

namespace E {
void Entity::AttachChild(Entity& child) {
    if (HasChild(child.Id)) {
        U::Logger::Error("Child Entity already exists: " + std::to_string(child.Id));
        return;
    }

    if (&child == this) {
        U::Logger::Error("An entity cannot be its own child.");
        return;
    }

    if (child.IsAncestorOf(*this)) {
        U::Logger::Error("An entity cannot have its ancestor as a child.");
        return;
    }

    if (child.HasParent()) {
        child.ClearParent();
    }

    Children.emplace_back(child.Id);

    child.Parent = this->Id;
}

std::vector<U::CheckedPtr<Entity>> Entity::GetChildren() {
    std::vector<U::CheckedPtr<Entity>> children;
    children.reserve(Children.size());

    for (unsigned int id : Children) {
        children.emplace_back(&World::Get().FindEntity(id));
    }

    return children;
}

std::vector<U::CheckedPtr<Component>> Entity::GetAllComponents() {
    std::vector<U::CheckedPtr<Component>> components;
    for (auto& component : Components | std::views::values) {
        components.emplace_back(&*component);
    }

    return components;
}

void Entity::Destroy() {
    World::Get().RemoveEntity(Id);
}

void Entity::DestroyChildren() {
    while (!Children.empty()) {
        DestroyChild(Children.back());
    }
}

void Entity::DestroyChild(unsigned int id) {
    if (!HasChild(id)) {
        return;
    }
    auto& child = World::Get().FindEntity(id);
    child.Destroy();
}

std::vector<U::CheckedPtr<Entity>> Entity::GetDescendants() {
    std::vector<U::CheckedPtr<Entity>> descendants;
    descendants.reserve(Children.size());

    RecursiveChildren(descendants, *this);

    return descendants;
}

bool Entity::HasDescendant(unsigned int id) const {
    U::CheckedPtr<Entity> descendant = World::Get().TryFindEntity(id);
    return descendant && descendant->IsDescendantOf(*this);
}

bool Entity::HasAncestor(unsigned int id) const {
    U::CheckedPtr<Entity> ancestor = World::Get().TryFindEntity(id);
    return ancestor && ancestor->IsAncestorOf(*this);
}

void Entity::DetachChild(unsigned int id) {
    auto it = std::ranges::find(Children, id);

    if (it != Children.end()) {
        World::Get().FindEntity(id).Parent = 0;
        Children.erase(it);
    }
}

void Entity::SetParent(Entity& parent) {
    parent.AttachChild(*this);
}

Entity& Entity::GetParent() {
    return World::Get().FindEntity(Parent);
}

void Entity::ClearParent() {
    if (HasParent()) {
        World::Get().FindEntity(Parent).DetachChild(Id);
    }
}

bool Entity::HasParent() const {
    return Parent != 0;
}

std::vector<U::CheckedPtr<Entity>> Entity::GetAncestors() {
    std::vector<U::CheckedPtr<Entity>> ancestors;

    unsigned int current = Parent;

    while (current != 0) {
        Entity& entity = World::Get().FindEntity(current);
        ancestors.emplace_back(&entity);
        current = entity.Parent;
    }

    return ancestors;
}

bool Entity::IsDescendantOf(const Entity& entity) {
    return std::ranges::any_of(GetAncestors(), [&entity](const auto& ancestor) {
        return ancestor->Id == entity.Id;
    });
}

bool Entity::IsAncestorOf(const Entity& entity) {
    return std::ranges::any_of(GetDescendants(), [&entity](const auto& descendant) {
        return descendant->Id == entity.Id;
    });
}

Entity& Entity::GetRoot() {
    U::CheckedPtr current = this;

    while (current->HasParent())
        current = &World::Get().FindEntity(current->Parent);

    return *current;
}

bool Entity::HasChild(unsigned int id) const {
    auto it = std::ranges::find(Children, id);
    return it != Children.end();
}

Entity& Entity::GetChild(unsigned int id) {
    if (HasChild(id)) {
        return World::Get().FindEntity(id);
    }

    U::Logger::Fatal(
        std::format("Entity {} has no child {}", Id, id)
    );
}

U::CheckedPtr<Entity> Entity::TryGetChild(unsigned int id) {
    if (HasChild(id)) {
        return &World::Get().FindEntity(id);
    }

    return nullptr;
}

size_t Entity::ChildCount() const {
    return Children.size();
}

void Entity::RecursiveChildren(
    std::vector<U::CheckedPtr<Entity>>& entities,
    Entity& entity
) {
    for (unsigned int id : entity.Children) {
        Entity& child = World::Get().FindEntity(id);

        entities.emplace_back(&child);
        RecursiveChildren(entities, child);
    }
}
} // namespace E
