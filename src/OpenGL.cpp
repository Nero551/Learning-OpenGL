#include "OpenGL.h"
#include <cmath>
#include <iostream>
#include <vector>
#include "Math/MathUtils.h"
#include "Math/Vector.h"
#include "Renderer/Renderer.h"
#include "Math/Matrix.h"

GLFWwindow *CreateWindow(int width, int height, const char *name) {
  GLFWwindow *window = glfwCreateWindow(width, height, name, NULL, NULL);
  if (!window) {
    std::cout << "Failed To Create Window";
  }
  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed To Initialize GLAD";
  }

  glViewport(0, 0, width, height);
  glfwSetFramebufferSizeCallback(window,
    [](GLFWwindow *window, int width, int height) { glViewport(0, 0, width, height); });

  return window;
}

void ProcessInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
}

void InitOpenGL() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void Bullshit() {
  Vector2 vec2 = Vector2(1, 2);

  Matrix2 mat2 = Matrix2::Identity;
  mat2 = mat2.Scale({2, 3});

  Matrix2 mat22 = Matrix2::Identity;
  mat22 = mat22.Scale({3, 5});

  Matrix3 mat3 = Matrix3::Identity;
  mat3 = mat3.Scale({2, 3, 5});

  auto result = mat2 * vec2;
  std::cout << mat3.Determinant();
  // TODO- just mess around with matrices , transformations , projection , all dat.
}

int main() {

  // float WindowWidth = 800;
  // float WindowHeight = 800;

  // InitOpenGL();
  // GLFWwindow *Window = CreateWindow(WindowWidth, WindowHeight, "Plus Ultra");

  // std::vector<Vertex> Vertices = {Vertex(Vector4(0.5, 0.5, 0.5, 1), Vector4(1, 0, 1, 1), Vector2(4, 4)),
  //   Vertex(Vector4(0.5, -0.5, 0.5, 1), Vector4(1, 1, 0, 1), Vector2(4, 0)),
  //   Vertex(Vector4(-0.5, -0.5, 0.5, 1), Vector4(0, 1, 1, 1), Vector2(0, 0)),
  //   Vertex(Vector4(-0.5, 0.5, 0.5, 1), Vector4(1, 1, 1, 1), Vector2(0, 4))};

  // std::vector<unsigned int> Indices = {0, 1, 2, 0, 2, 3};

  Bullshit();

  // Texture texture(0, "src/Images/ruby.png");
  // Shader shader("src/Shaders/shader.frag", "src/Shaders/shader.vert");
  // Material material(shader);
  // material.Texture0 = &texture;
  // Geometry geometry(Vertices, Indices);

  // while (!glfwWindowShouldClose(Window)) {
  //   glClearColor(0.1, 0.15, 0.2, 1);
  //   glClear(GL_COLOR_BUFFER_BIT);

  //   material.Use();
  //   // model = model.RotateZ(Math::DegToRad(16));
  //   material.Shader.SetMat4("uModel", model);
  //   material.Shader.SetMat4("uView", view);
  //   material.Shader.SetMat4("uProjection", projection);

  //   geometry.Draw();

  //   glfwSwapBuffers(Window);

  //   ProcessInput(Window);
  //   glfwPollEvents();
  // }

  // glfwTerminate();
  return 0;
}