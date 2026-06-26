#pragma once
#include "../Math/Math.h"

struct Vertex{
    Vector3 Position;
    Vector4 Color;
    Vertex(Vector3 pos, Vector4 col);
};