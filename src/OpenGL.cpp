#include "OpenGL.h"
#include "Engine/Engine.h"
#include "Math/MathUtils.h"
#include "Math/Matrix/Matrix.h"
#include "Math/Vector/Vector.h"
#include "Renderer/Renderer.h"
#include "Services/LoggerService.h"
#include <GL/gl.h>
#include <cmath>
#include <iostream>
#include <vector>

int main() {
  glfwInit();
  Window window(800, 800, "Plus Ultra");
  glEnable(GL_DEPTH_TEST);

  std::vector<Vertex> Vertices = {
    // front face
    Vertex({-0.5, -0.5, 0.5, 1}, {1, 0, 0, 1}, {0, 0}), // 0
    Vertex({0.5, -0.5, 0.5, 1}, {0, 1, 0, 1}, {1, 0}),  // 1
    Vertex({0.5, 0.5, 0.5, 1}, {0, 0, 1, 1}, {1, 1}),   // 2
    Vertex({-0.5, 0.5, 0.5, 1}, {1, 0, 1, 1}, {0, 1}),  // 3

    // back face
    Vertex({-0.5, -0.5, -0.5, 1}, {1, 0, 0, 1}, {1, 0}), // 4
    Vertex({0.5, -0.5, -0.5, 1}, {0, 1, 0, 1}, {0, 0}),  // 5
    Vertex({0.5, 0.5, -0.5, 1}, {0, 0, 1, 1}, {0, 1}),   // 6
    Vertex({-0.5, 0.5, -0.5, 1}, {1, 0, 1, 1}, {1, 1})   // 7
  };
  std::vector<unsigned int> Indices = {// front
    0, 1, 2, 2, 3, 0,

    // back
    5, 4, 7, 7, 6, 5,

    // left
    4, 0, 3, 3, 7, 4,

    // right
    1, 5, 6, 6, 2, 1,

    // top
    3, 2, 6, 6, 7, 3,

    // bottom
    4, 5, 1, 1, 0, 4};
  Matrix4 model = Matrix4::Identity;
  model = model.RotateX(Math::DegToRad(120));
  model = model.RotateZ(Math::DegToRad(45));

  Matrix4 view = Matrix4::Identity;
  view = view.Translate({0, 0, -3});

  Matrix4 projection = Matrix4::Perspective(Math::DegToRad(45), 800.0f / 800.0f, 0.1, 100);

  Texture texture(0, "src/Images/ruby.png");
  Shader shader("src/Shaders/shader.frag", "src/Shaders/shader.vert");
  Material material(shader);
  material.Texture0 = &texture;
  Mesh mesh(Vertices, Indices);

  Object object;
  object.AssignMaterial(material);
  object.AssignMesh(mesh);

  while (!window.ShouldClose()) {
    glClearColor(0.1, 0.15, 0.2, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    object.ModelMatrix = object.ModelMatrix.RotateY(Math::DegToRad(2));
    object.ModelMatrix = object.ModelMatrix.RotateX(Math::DegToRad(2));

    object.Draw(view, projection);

    window.SwapBuffers();
    window.ProcessInput();
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}