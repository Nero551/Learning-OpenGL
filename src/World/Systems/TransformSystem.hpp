#pragma once

#include "Core/OuterCore/ECS/System.hpp"

namespace E {
struct TransformSystem : System {
    void Start() override;

    void Update(double dt) override;
};
}
