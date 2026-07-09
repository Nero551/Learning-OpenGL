#include "Camera.hpp"

#include "Core/Engine.hpp"
#include "Utilities/Math/MathUtils.hpp"
#include "Utilities/Math/Matrix/Matrix4.hpp"

#include <cmath>

Matrix4 Camera::GetViewMatrix() {
  return Matrix4::LookAt(Position, Position + Front, GetUp());
  ;
}

Matrix4 Camera::GetProjectionMatrix() {
  Matrix4 projection = Matrix4::Perspective(Math::DegToRad(FOV),
    static_cast<float>(Engine::Instance->window.Width) / static_cast<float>(Engine::Instance->window.Height), 0.1, 100);
  return projection;
}

Vector3 Camera::GetRight() { return Vector3(0, 1, 0).Cross(Front).Normalized(); }
Vector3 Camera::GetUp() { return Front.Cross(GetRight()).Normalized(); }

void Camera::ComputeFront() {
  if (firstMouse) {
    lastX = Engine::Instance->ModuleStore.InputModule.MousePosition.x;
    lastY = Engine::Instance->ModuleStore.InputModule.MousePosition.y;
    firstMouse = false;
  }

  float xOffset = Engine::Instance->ModuleStore.InputModule.MousePosition.x - lastX;
  float yOffset = lastY - Engine::Instance->ModuleStore.InputModule.MousePosition.y;
  xOffset *= Sensitivity;
  yOffset *= Sensitivity;

  lastX = Engine::Instance->ModuleStore.InputModule.MousePosition.x;
  lastY = Engine::Instance->ModuleStore.InputModule.MousePosition.y;

  Yaw += xOffset;
  Pitch += yOffset;
  Pitch = Pitch > 89.0f ? 89.0f : Pitch;
  Pitch = Pitch < -89.0f ? -89.0f : Pitch;

  Vector3 direction;
  direction.x = std::cos(Math::DegToRad(Yaw)) * std::cos(Math::DegToRad(Pitch));
  direction.y = std::sin(Math::DegToRad(Pitch));
  direction.z = std::sin(Math::DegToRad(Yaw)) * std::cos(Math::DegToRad(Pitch));

  Front = direction.Normalized();
}