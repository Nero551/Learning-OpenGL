#pragma once

#include "Core/OuterCore/ECS/System.hpp"

namespace E {
struct Transform3DSystem : System {
    void Start() override;

    void Update(double dt) override;
};
}
