#include "Renderer.h"
#include <vector>

void Object::AssignMaterial(struct Material &material) { Material = &material; }
void Object::AssignMesh(class Mesh &mesh) { Mesh = &mesh; }

void Object::Draw(Matrix4 viewMatrix, Matrix4 projectionMatrix) {
  if (Material) {
    Material->Use();
    Material->Shader.SetMat4("uModel", ModelMatrix);
    Material->Shader.SetMat4("uView", viewMatrix);
    Material->Shader.SetMat4("uProjection", projectionMatrix);
  }
  if (Mesh) {
    Mesh->Draw();
  }
}