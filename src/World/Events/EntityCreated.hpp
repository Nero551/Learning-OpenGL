#pragma once
#include "Core/OuterCore/Entity.hpp"
#include "Core/OuterCore/Event.hpp"


struct EntityCreated : Event {
    Entity& entity;

    EntityCreated(Entity& entity) : entity(entity) {}
};
