#pragma once
#include "Core/OuterCore/System.hpp"
#include "Utilities/Math/Matrix/Matrix4.hpp"

struct CameraSystem : System {

  void Update(double dt) override;
  Matrix4 GetViewMatrix();
};