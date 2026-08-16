#include "Scene.hpp"

#include "Core/InnerCore/World.hpp"

E::Entity& E::Scene::GetRoot() {
    return World::Get().FindEntity(Root);
}

void E::Scene::SetRoot(Entity& entity) {
    Root = entity.Id;
}

void E::Scene::SetRoot(unsigned int entityId) {
    Root = entityId;
}
