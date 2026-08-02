#pragma once
#include "Core/OuterCore/ECS/System.hpp"
#include "Utilities/Math/Matrix/Matrix4.hpp"

namespace E {
    struct CameraSystem : System {
        void Update(double dt) override;
        Matrix4 GetViewMatrix();
    };
}
