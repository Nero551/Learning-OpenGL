#pragma once

#include "Core/OuterCore/System.hpp"

struct TransformSystem : System {
    void Start() override;

    void Update(double dt) override;
};
