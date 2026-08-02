#pragma once
#include "Core/OuterCore/ECS/Entity.hpp"

struct Nova : E::Entity {
    void Initialize() override {
        Entity::Initialize();
    }
};
