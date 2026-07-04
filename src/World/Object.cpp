#include "World.h"
#include "Utilities/Math/Matrix/Matrix.h"
#include <vector>

Object::Object(class Mesh mesh, struct Material material) : Material(material), Mesh(mesh) {}

void Object::Draw(Matrix4 viewMatrix, Matrix4 projectionMatrix) {
  Material.Use();
  Material.Shader.SetMat4("uModel", ModelMatrix);
  Material.Shader.SetMat4("uView", viewMatrix);
  Material.Shader.SetMat4("uProjection", projectionMatrix);
  Mesh.Draw();
}