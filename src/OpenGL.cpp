#include <cmath>
#include <iostream>
#include <vector>
#include "Engine/Engine.h"
#include "Renderer/Renderer.h"
#include "Math/Math.h"
#include "Services/Service.h"

void Bullshit() {
  Vector3 vec3 = Vector3(1, 0, 0);
  Vector3 vec33 = Vector3(0, 1, 0);
  Matrix4 mat4 = Matrix4::Identity;
  mat4 = mat4.Translate({1, 2, 3});
  mat4 = mat4.Scale({2, 3, 4});

  Vector2 vec2 = {1, 2};
  Matrix2 mat2 = Matrix2::Identity;
  mat2 = mat2.Scale({2, 3});

  LoggerService::Info(mat2 * vec2);
}

int main() {
  Bullshit();

  glfwInit();
  Window window(800, 800, "Plus Ultra");

  std::vector<Vertex> Vertices = {Vertex(Vector4(0.5, 0.5, 0.5, 1), Vector4(1, 0, 1, 1), Vector2(4, 4)),
    Vertex(Vector4(0.5, -0.5, 0.5, 1), Vector4(1, 1, 0, 1), Vector2(4, 0)),
    Vertex(Vector4(-0.5, -0.5, 0.5, 1), Vector4(0, 1, 1, 1), Vector2(0, 0)),
    Vertex(Vector4(-0.5, 0.5, 0.5, 1), Vector4(1, 1, 1, 1), Vector2(0, 4))};

  std::vector<unsigned int> Indices = {0, 1, 2, 0, 2, 3};

  Texture texture(0, "src/Images/ruby.png");
  Shader shader("src/Shaders/shader.frag", "src/Shaders/shader.vert");
  Material material(shader);
  material.Texture0 = &texture;
  Geometry geometry(Vertices, Indices);

  while (!window.ShouldClose()) {
    glClearColor(0.1, 0.15, 0.2, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    material.Use();
    // material.Shader.SetMat4("uModel", model);
    // material.Shader.SetMat4("uView", view);
    // material.Shader.SetMat4("uProjection", projection);

    geometry.Draw();

    window.SwapBuffers();

    window.ProcessInput();
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}