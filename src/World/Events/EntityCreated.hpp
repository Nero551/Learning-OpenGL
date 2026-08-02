#pragma once
#include "Core/OuterCore/ECS/Entity.hpp"
#include "Core/OuterCore/Event.hpp"

namespace E {
    struct EntityCreated : Event {
        E::Entity& entity;

        EntityCreated(E::Entity& entity) : entity(entity) {}
    };
}
