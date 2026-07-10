#pragma once
#include "Core/System.hpp"

struct CameraSystem : System {

  void Update(double dt) override;

private:
  const float cameraSpeed = 5;
  bool firstMouse = true;
  float lastX = 800 / 2;
  float lastY = 600 / 2;
};