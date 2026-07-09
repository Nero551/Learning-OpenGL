#pragma once
#include "Utilities/Math/Matrix/Matrix4.hpp"

struct Camera {
  Vector3 Position;
  Vector3 Up = Vector3(0.0f, 1.0f, 0.0f);
  Vector3 Front = Vector3(0.0f, 0.0f, -1.0f);

  Matrix4 GetViewMatrix();
  Matrix4 GetProjectionMatrix();
  Vector3 GetRight();
};