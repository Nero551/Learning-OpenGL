export module World;

import Material;
import Math;
import Mesh;

export struct World {
  // TODO- this guy should own runtime world state (stuff that exist).
};

export struct Object {
  Object(Mesh mesh, Material material) : material(material), mesh(mesh) {}

  void Draw(Matrix4 viewMatrix, Matrix4 projectionMatrix) {
    material.Use();
    material.shader.SetMat4("uModel", ModelMatrix);
    material.shader.SetMat4("uView", viewMatrix);
    material.shader.SetMat4("uProjection", projectionMatrix);
    mesh.Draw();
  }

  Material material;
  Mesh mesh;
  Matrix4 ModelMatrix = Matrix4::Identity;
};
