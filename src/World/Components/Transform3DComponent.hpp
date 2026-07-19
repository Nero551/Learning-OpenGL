#pragma once

#include "Core/OuterCore/Component.hpp"
#include "Utilities/Dirty.hpp"
#include "Utilities/Math/Matrix/Matrix4.hpp"

struct Transform3DComponent : Component {
    Dirty<Vector3> LocalPosition = Vector3::Zero;
    Vector3 LocalEulerRotation = Vector3::Zero; // Radians
    Vector3 LocalScale = Vector3::One;

    Dirty<Vector3> GlobalPosition = Vector3::Zero;
    Vector3 GlobalEulerRotation = Vector3::Zero;
    Vector3 GlobalScale = Vector3::One;

    bool InheritTransform = true;

    [[nodiscard]] Matrix4 GetModelMatrix() {
        Matrix4 modelMatrix = Matrix4::Identity;
        modelMatrix = modelMatrix.Translate(LocalPosition);
        modelMatrix = modelMatrix.Rotate(LocalEulerRotation);
        modelMatrix = modelMatrix.Scale(LocalScale);

        return modelMatrix;
    }

    [[nodiscard]] Matrix3 GetNormalMatrix() {
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
        direction.x = std::sin(LocalEulerRotation.y) * std::cos(LocalEulerRotation.x);
        direction.y = std::sin(LocalEulerRotation.x);
        direction.z = std::cos(LocalEulerRotation.y) * std::cos(LocalEulerRotation.x);

        return direction.Normalized();
    }
};
