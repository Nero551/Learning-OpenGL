#pragma once
#include "Utilities/Math/Matrix/Matrix4.hpp"

struct Camera {

  float Yaw = -90.0f;
  float Pitch;
  float Sensitivity = 0.05f;
  float FOV = 45.0f;
  Vector3 Position;
  Vector3 Front = Vector3(0.0f, 0.0f, -1.0f);

  Matrix4 GetViewMatrix();
  Matrix4 GetProjectionMatrix();
  Vector3 GetRight();
  Vector3 GetUp();
  void ComputeFront();

private:
  float lastX;
  float lastY;
};