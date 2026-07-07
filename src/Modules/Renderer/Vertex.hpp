#pragma once
#include "Utilities/Math/Vector/Vector.hpp"

struct Vertex {
  Vector4 Position;
  Vector4 Color;
  Vector2 UV;

  Vertex(Vector4 pos, Vector4 col, Vector2 uv);
};