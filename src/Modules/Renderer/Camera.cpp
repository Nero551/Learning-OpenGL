#include "Camera.hpp"

#include "Utilities/Math/MathUtils.hpp"
#include "Utilities/Math/Matrix/Matrix4.hpp"

Matrix4 Camera::GetViewMatrix() {
  Matrix4 view = Matrix4::Identity;
  view = view.Translate({0, 0, -3});
  return view;
}

Matrix4 Camera::GetProjectionMatrix() {
  Matrix4 projection = Matrix4::Perspective(Math::DegToRad(45), 800.0f / 800.0f, 0.1, 100);
  return projection;
}
Vector3 Camera::GetDirection() { return (Position - Direction).Normalized(); }

Vector3 Camera::GetRight() { return GetDirection().Cross({0, 1, 0}).Normalized(); }
Vector3 Camera::GetUp() { return GetDirection().Cross(GetRight()).Normalized(); }
