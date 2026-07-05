#pragma once
#include <memory>
#include <vector>
#include "Modules/Renderer/Renderer.hpp"

struct World {
  // TODO- this guy should own runtime world state (stuff that exist).
};

struct Object {
  Object(class Mesh mesh, struct Material material);
  void Draw(Matrix4 viewMatrix, Matrix4 projectionMatrix);

  std::shared_ptr<Material> Material;
  std::shared_ptr<Mesh> Mesh;
  Matrix4 ModelMatrix = Matrix4::Identity;
};