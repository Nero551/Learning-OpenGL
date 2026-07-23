#pragma once

#include "Core/OuterCore/ECS/Component.hpp"
#include "Utilities/Math/MathUtils.hpp"
#include "Utilities/Math/Matrix/Matrix4.hpp"

struct CameraComponent : Component {
    float FOV = 45.0f;
    float Sensitivity = 0.05f;
    float Near = 0.1f;
    float Far = 100.0f;
    float AspectRatio = 1.0f;
    float Speed = 5.0f;

    Matrix4 GetProjectionMatrix() const {
        return Matrix4::Perspective(Math::Radians(FOV), AspectRatio, Near, Far);
    }
};
