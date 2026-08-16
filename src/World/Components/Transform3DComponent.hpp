#pragma once

#include "Core/OuterCore/ECS/Component.hpp"
#include "Math/Matrix/Matrix4.hpp"

namespace E {
struct Transform3DComponent : Component {
    M::Vector3 Position = M::Vector3::Zero;
    M::Vector3 Rotation = M::Vector3::Zero; // Radians
    M::Vector3 Scale = M::Vector3::One;

    bool InheritTransform = true;

    [[nodiscard]] M::Matrix4 GetModelMatrix() const {
        M::Matrix4 modelMatrix = M::Matrix4::Identity;
        modelMatrix = modelMatrix.Translate(GlobalPosition);
        modelMatrix = modelMatrix.Rotate(GlobalRotation);
        modelMatrix = modelMatrix.Scale(GlobalScale);

        return modelMatrix;
    }

    [[nodiscard]] M::Matrix3 GetNormalMatrix() const {
        return GetModelMatrix().ToMatrix3().Inverse().Transpose();
    }

    [[nodiscard]] M::Vector3 GetRight() const {
        return M::Vector3::Up.Cross(GetForward()).Normalized();
    }

    [[nodiscard]] M::Vector3 GetUp() const {
        return GetForward().Cross(GetRight()).Normalized();
    }

    [[nodiscard]] M::Vector3 GetForward() const {
        M::Vector3 direction;
        direction.x = std::sin(Rotation.y) * std::cos(Rotation.x);
        direction.y = std::sin(Rotation.x);
        direction.z = std::cos(Rotation.y) * std::cos(Rotation.x);

        return direction.Normalized();
    }

private:
    // TODO- this is temporary until i have a proper change detection system
    // (reflection)
    M::Vector3 GlobalPosition = M::Vector3::Zero;
    M::Vector3 GlobalRotation = M::Vector3::Zero; // Radians
    M::Vector3 GlobalScale = M::Vector3::One;
    friend struct Transform3DSystem;
};
} // namespace E
