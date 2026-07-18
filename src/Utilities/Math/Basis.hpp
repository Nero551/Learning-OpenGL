#pragma once
#include "Matrix/Matrix4.hpp"
#include "Vector/Vector3.hpp"

struct Basis {
  Vector3 Right = Vector3::Right;
  Vector3 Up = Vector3::Up;
  Vector3 Forward = Vector3::Forward;

  [[nodiscard]] Matrix4 GetMatrix() const;
  [[nodiscard]] Matrix4 GetInverseMatrix() const;
};