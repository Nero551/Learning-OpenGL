#pragma once
#include <vector>
#include "Modules/Renderer/Renderer.h"

struct World {
  // TODO- this guy should own runtime world state (stuff that exist).
};

struct Object {

  Object(class Mesh mesh, struct Material material);
  void Draw(Matrix4 viewMatrix, Matrix4 projectionMatrix);

  Material Material;
  Mesh Mesh;
  Matrix4 ModelMatrix = Matrix4::Identity;
};