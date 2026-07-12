#pragma once

#include <cmath>

#include "Core/Component.hpp"
#include "Utilities/Math/Matrix/Matrix4.hpp"

struct TransformComponent : Component {
   Vector3 Position = Vector3::Zero;
   Vector3 EulerRotation = Vector3::Zero; // Radians
   Vector3 Scale = Vector3::One;

   Matrix4 GetModelMatrix() const {
      Matrix4 modelMatrix = Matrix4::Identity;
      modelMatrix = modelMatrix.Translate(Position);
      modelMatrix = modelMatrix.Rotate(EulerRotation);
      modelMatrix = modelMatrix.Scale(Scale);

      return modelMatrix;
   }

   Matrix3 GetNormalMatrix() const {
      Matrix3 normalMatrix = GetModelMatrix().ToMatrix3().Inverse().Transpose();;
      return normalMatrix;
   }

   Vector3 GetRight() const { return Vector3::Up.Cross(GetForward()).Normalized(); }
   Vector3 GetUp() const { return GetForward().Cross(GetRight()).Normalized(); }

   Vector3 GetForward() const {
      Vector3 direction;
      direction.x = std::sin(EulerRotation.y) * std::cos(EulerRotation.x);
      direction.y = std::sin(EulerRotation.x);
      direction.z = std::cos(EulerRotation.y) * std::cos(EulerRotation.x);

      return direction.Normalized();
   }
};
