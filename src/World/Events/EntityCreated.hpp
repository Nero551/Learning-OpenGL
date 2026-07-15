#pragma once
#include "Core/Entity.hpp"
#include "Core/Event.hpp"


struct EntityCreated : Event {
    Entity& entity;

    EntityCreated(Entity& entity) : entity(entity) {}
};
