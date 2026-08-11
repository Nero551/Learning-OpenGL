#pragma once

#include "Core/OuterCore/ECS/Component.hpp"
#include "Utilities/Math/MathUtils.hpp"
#include "Utilities/Math/Matrix/Matrix4.hpp"

namespace E {
    struct CameraComponent : Component {
        float FOV = 45.0f;
        float Sensitivity = 0.05f;
        float Near = 0.1f;
        float Far = 100.0f;
        float AspectRatio = 1.0f;
        float Speed = 5.0f;

        [[nodiscard]] M::Matrix4 GetProjectionMatrix() const {
            return M::Matrix4::Perspective(M::Rad(FOV), AspectRatio, Near, Far);
        }
    };
}
