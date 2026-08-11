#pragma once

#include "Core/OuterCore/ECS/Component.hpp"
#include "Utilities/Math/Matrix/Matrix4.hpp"

namespace E {
struct Transform3DComponent : Component {
    Vector3 Position = Vector3::Zero;
    Vector3 Rotation = Vector3::Zero; // Radians
    Vector3 Scale = Vector3::One;

    bool InheritTransform = true;

    [[nodiscard]] Matrix4 GetModelMatrix() const {
        Matrix4 modelMatrix = Matrix4::Identity;
        modelMatrix = modelMatrix.Translate(GlobalPosition);
        modelMatrix = modelMatrix.Rotate(GlobalRotation);
        modelMatrix = modelMatrix.Scale(GlobalScale);

        return modelMatrix;
    }

    [[nodiscard]] Matrix3 GetNormalMatrix() const {
        return GetModelMatrix().ToMatrix3().Inverse().Transpose();
    }

    [[nodiscard]] Vector3 GetRight() const {
        return Vector3::Up.Cross(GetForward()).Normalized();
    }

    [[nodiscard]] Vector3 GetUp() const {
        return GetForward().Cross(GetRight()).Normalized();
    }

    [[nodiscard]] Vector3 GetForward() const {
        Vector3 direction;
        direction.x = std::sin(Rotation.y) * std::cos(Rotation.x);
        direction.y = std::sin(Rotation.x);
        direction.z = std::cos(Rotation.y) * std::cos(Rotation.x);

        return direction.Normalized();
    }

private:
    //TODO- this is temporary until i have a proper change detection system (reflection)
    Vector3 GlobalPosition = Vector3::Zero;
    Vector3 GlobalRotation = Vector3::Zero; // Radians
    Vector3 GlobalScale = Vector3::One;
    friend struct TransformSystem;
};
}
