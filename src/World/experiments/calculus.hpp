#pragma once

#include "Core/OuterCore/ECS/System.hpp"

namespace E {
struct calculus : System {
    void Start() override;

    void Update(double dt) override;
};
} // namespace E
