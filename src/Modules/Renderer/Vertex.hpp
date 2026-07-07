#pragma once
#include "Utilities/Math/Vector/Vector2.hpp"
#include "Utilities/Math/Vector/Vector4.hpp"

struct Vertex {
  Vector4 Position;
  Vector4 Color;
  Vector2 UV;

  Vertex(Vector4 pos, Vector4 col, Vector2 uv);
};