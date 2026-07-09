#pragma once
#include "Utilities/Math/Matrix/Matrix4.hpp"
#include "Utilities/Math/Vector/Vector4.hpp"

struct Camera {
  Vector3 Position;
  Vector3 Direction;
  Vector3 Target;

  Matrix4 GetViewMatrix();
  Matrix4 GetProjectionMatrix();
  Vector3 GetDirection();
  Vector3 GetUp();
  Vector3 GetRight();
};