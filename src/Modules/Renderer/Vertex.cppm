module;

export module Vertex;

export import Vector2;
export import Vector4;

export struct Vertex {
  Vector4 Position;
  Vector4 Color;
  Vector2 UV;

  Vertex(Vector4 pos, Vector4 col, Vector2 uv) : Position(pos), Color(col), UV(uv) {}
};
