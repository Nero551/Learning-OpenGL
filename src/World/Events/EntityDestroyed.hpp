#pragma once
#include "Core/OuterCore/ECS/Entity.hpp"
#include "Core/OuterCore/Event.hpp"

namespace E {
    struct EntityDestroyed : Event {
        Entity& entity;

        EntityDestroyed(Entity& entity) : entity(entity) {}
    };
}
