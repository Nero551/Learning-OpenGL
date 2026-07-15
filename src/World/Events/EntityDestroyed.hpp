#pragma once
#include "Core/OuterCore/Entity.hpp"
#include "Core/OuterCore/Event.hpp"


struct EntityDestroyed : Event {
    Entity& entity;

    EntityDestroyed(Entity& entity) : entity(entity) {}
};
