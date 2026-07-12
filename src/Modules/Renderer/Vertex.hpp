#pragma once
#include "Utilities/Math/Vector/Vector2.hpp"
#include "Utilities/Math/Vector/Vector3.hpp"
#include "Utilities/Math/Vector/Vector4.hpp"

struct Vertex {
   Vector4 Position;
   Vector4 Color;
   Vector2 UV;
   Vector3 Normal;

   Vertex(Vector4 pos, Vector4 col, Vector2 uv, Vector3 normal) : Position(pos), Color(col), UV(uv), Normal(normal) {}
};
