#pragma once

#include "Core/Component.hpp"
#include "Utilities/Math/Matrix/Matrix4.hpp"
#include "Utilities/Math/Vector/Vector3.hpp"

struct TransformComponent : Component {
  Vector3 Position{0, 0, 0};
  Vector3 EulerRotation{0, 0, 0}; // Radians
  Vector3 Scale{1, 1, 1};
  Vector3 Forward{0, 0, -1};

  Matrix4 GetModelMatrix() const {
    Matrix4 modelMatrix = Matrix4::Identity;
    modelMatrix = modelMatrix.Translate(Position);
    modelMatrix = modelMatrix.Rotate(EulerRotation);
    modelMatrix = modelMatrix.Scale(Scale);

    return modelMatrix;
  }

  Vector3 GetRight() const { return Vector3(0, 1, 0).Cross(Forward).Normalized(); }
  Vector3 GetUp() const { return Forward.Cross(GetRight()).Normalized(); }
};