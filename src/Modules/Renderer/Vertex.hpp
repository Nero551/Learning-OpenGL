#pragma once
#include "Math/Vector/Vector2.hpp"
#include "Math/Vector/Vector3.hpp"
#include "Math/Vector/Vector4.hpp"

namespace E {
struct Vertex {
    M::Vector4 Position;
    M::Vector4 Color;
    M::Vector2 UV;
    M::Vector3 Normal;

    Vertex(M::Vector4 pos, M::Vector4 col, M::Vector2 uv, M::Vector3 normal) : Position(pos), Color(col), UV(uv),
        Normal(normal) {}
};
}
