#pragma once
#include "Core/OuterCore/ECS/Entity.hpp"
#include "Core/OuterCore/Event.hpp"


struct EntityDestroyed : Event {
    E::Entity& entity;

    EntityDestroyed(E::Entity& entity) : entity(entity) {}
};
