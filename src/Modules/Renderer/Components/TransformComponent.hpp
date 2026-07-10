#pragma once

#include "Core/Component.hpp"
#include "Utilities/Math/Matrix/Matrix4.hpp"
#include "Utilities/Math/Vector/Vector3.hpp"

#include <cmath>

struct TransformComponent : Component {
  Vector3 Position{0, 0, 0};
  Vector3 EulerRotation{0, 0, 0}; // Radians
  Vector3 Scale{1, 1, 1};

  Matrix4 GetModelMatrix() const {
    Matrix4 modelMatrix = Matrix4::Identity;
    modelMatrix = modelMatrix.Translate(Position);
    modelMatrix = modelMatrix.Rotate(EulerRotation);
    modelMatrix = modelMatrix.Scale(Scale);

    return modelMatrix;
  }

  Vector3 GetRight() const { return GetForward().Cross(Vector3(0, 1, 0)).Normalized(); }
  Vector3 GetUp() const { return GetRight().Cross(GetForward()).Normalized(); }
  
  Vector3 GetForward() const {
    Vector3 direction;
    direction.x = std::cos(EulerRotation.y) * std::cos(EulerRotation.x);
    direction.y = std::sin(EulerRotation.x);
    direction.z = std::sin(EulerRotation.y) * std::cos(EulerRotation.x);

    return direction.Normalized();
  }
};