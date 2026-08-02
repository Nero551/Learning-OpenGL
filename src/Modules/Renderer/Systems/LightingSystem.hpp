#pragma once
#include "Core/OuterCore/ECS/System.hpp"

namespace E {
struct LightingSystem : System {
    void Start() override;
    void Render() override;
};
}
