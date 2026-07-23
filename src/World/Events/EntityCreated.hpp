#pragma once
#include "Core/OuterCore/ECS/Entity.hpp"
#include "Core/OuterCore/Event.hpp"


struct EntityCreated : Event {
    Entity& entity;

    EntityCreated(Entity& entity) : entity(entity) {}
};
