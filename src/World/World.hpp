#pragma once

#include "Modules/Renderer/Material.hpp"
#include "Modules/Renderer/Mesh.hpp"
#include "Utilities/Math/Matrix/Matrix.hpp"

struct World {
  // TODO- this guy should own runtime world state (stuff that exist).
};

struct Object {
  Object(Mesh mesh, Material material);
  void Draw(Matrix4 viewMatrix, Matrix4 projectionMatrix);

  Material Material;
  Mesh Mesh;
  Matrix4 ModelMatrix = Matrix4::Identity;
};