#pragma once

#include "Core/OuterCore/System.hpp"

struct TransformSystem : System {
    void Start() override;

    void FixedUpdate(double fdt) override;
};
