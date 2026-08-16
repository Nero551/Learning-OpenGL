#pragma once
#include "Core/OuterCore/ECS/Entity.hpp"
#include "Core/OuterCore/Event.hpp"

namespace E {
struct EntityCreated : Event {
    Entity& entity;

    EntityCreated(Entity& entity) : entity(entity) {
    }
};
} // namespace E
