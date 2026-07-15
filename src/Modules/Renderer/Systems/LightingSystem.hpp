#pragma once
#include "Core/OuterCore/System.hpp"

struct LightingSystem : System {
    void Start() override;
    void Render() override;
};
