#include "World.hpp"
#include "Modules/Renderer/Renderer.hpp"
#include "Utilities/Math/Matrix/Matrix.hpp"
#include <vector>

Object::Object(class Mesh mesh, struct Material material)
    : Material(std::make_shared<Material>(material)), Mesh(std::make_shared<Mesh>(mesh)) {}

void Object::Draw(Matrix4 viewMatrix, Matrix4 projectionMatrix) {
  Material->Use();
  Material->Shader.SetMat4("uModel", ModelMatrix);
  Material->Shader.SetMat4("uView", viewMatrix);
  Material->Shader.SetMat4("uProjection", projectionMatrix);
  Mesh->Draw();
}