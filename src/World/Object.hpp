#pragma once

#include "Modules/Renderer/Resources/Material.hpp"
#include "Modules/Renderer/Resources/Mesh.hpp"
#include "Utilities/Math/Matrix/Matrix4.hpp"

struct Object {
  Object(Mesh &mesh, Material &material);
  void Draw(Matrix4 viewMatrix, Matrix4 projectionMatrix);

  Material Material;
  Mesh Mesh;
  Matrix4 ModelMatrix = Matrix4::Identity;
};