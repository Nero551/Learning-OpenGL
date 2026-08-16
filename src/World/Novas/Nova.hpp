#pragma once
#include "Core/OuterCore/ECS/Entity.hpp"

namespace E {
struct Nova : Entity {
    void Initialize() override {
        Entity::Initialize();
    }
};
} // namespace E
