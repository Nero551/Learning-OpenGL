#pragma once
#include "Core/OuterCore/ECS/System.hpp"
#include "Math/Matrix/Matrix4.hpp"

namespace E {
struct CameraSystem : System {
    void Update(double dt) override;
    M::Matrix4 GetViewMatrix();
};
} // namespace E
