#pragma once
#include "Core/OuterCore/ECS/System.hpp"

struct LightingSystem : System {
    void Start() override;
    void Render() override;
};
