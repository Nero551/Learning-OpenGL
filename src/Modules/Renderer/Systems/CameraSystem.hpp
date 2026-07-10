#pragma once
#include "Core/System.hpp"
#include "Utilities/Math/Matrix/Matrix4.hpp"

struct CameraSystem : System {

  void Update(double dt) override;
  Matrix4 GetViewMatrix();

private:
  const float cameraSpeed = 5;
  bool firstMouse = true;
  float lastX = 800 / 2;
  float lastY = 600 / 2;
};