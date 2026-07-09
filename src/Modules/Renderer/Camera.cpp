#include "Camera.hpp"

#include "Utilities/Math/MathUtils.hpp"
#include "Utilities/Math/Matrix/Matrix4.hpp"

Matrix4 Camera::GetViewMatrix() {
  Matrix4 view = Matrix4::Identity;

  // TODO- make a LookAt() method in Matrix4 , so i can do view.LookAt(Position, Target, Up)
  view = Matrix4::LookAt(Position, Position + Front, Up);
  return view;
}

Matrix4 Camera::GetProjectionMatrix() {
  Matrix4 projection = Matrix4::Perspective(Math::DegToRad(45), 800.0f / 800.0f, 0.1, 100);
  return projection;
}

Vector3 Camera::GetRight() { return Front.Cross(Up).Normalized(); }
