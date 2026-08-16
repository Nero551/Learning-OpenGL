#pragma once
#include "Core/OuterCore/Event.hpp"
#include "Core/OuterCore/ECS/Entity.hpp"

namespace E {
struct EntityCreated : Event {
    Entity& entity;

    EntityCreated(Entity& entity) : entity(entity) {}
};
} // namespace E
