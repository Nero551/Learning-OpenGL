#include "Scene.hpp"

#include "Core/InnerCore/World.hpp"

E::Entity& E::Scene::GetRoot() {
    return World::Get().FindEntity(Root);
}

void E::Scene::SetRoot(const Entity& entity) {
    Root = entity.Id;
}

void E::Scene::SetRoot(const unsigned int entityId) {
    Root = entityId;
}
