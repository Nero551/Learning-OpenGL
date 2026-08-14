#pragma once

#include "Core/OuterCore/ECS/Component.hpp"
#include "Modules/Renderer/Enums/ProjectionMode.hpp"
#include "Utilities/Math/Common/Trigonometry.hpp"
#include "Utilities/Math/Matrix/Matrix4.hpp"

namespace E {
struct CameraComponent : Component {
    float FOV = 45.0f;
    float Sensitivity = 0.05f;
    float Near = 0.1f;
    float Far = 100.0f;
    float AspectRatio = 1.0f;
    float Speed = 5.0f;
    ProjectionMode ProjectionMode = ProjectionMode::Perspective;

    [[nodiscard]] M::Matrix4 GetProjectionMatrix() const {
        //TODO- currently , orthographic doesn't fucking work
        if (ProjectionMode == ProjectionMode::Orthographic) {
            return M::Matrix4::Orthographic(-AspectRatio, AspectRatio, -AspectRatio, AspectRatio, Near, Far);
        }
        return M::Matrix4::Perspective(M::Rad(FOV), AspectRatio, Near, Far);
    }
};
}
