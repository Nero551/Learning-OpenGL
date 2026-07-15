#pragma once
#include "Core/System.hpp"

struct LightingSystem : System {
    void Start() override;
    void Render() override;
};
