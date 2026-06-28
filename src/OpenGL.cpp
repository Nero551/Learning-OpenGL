#include "OpenGL.h"
#include <GLFW/glfw3.h>
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

int main() {
  Matrix4 trans = Matrix4::Identity;

  int WindowWidth = 800;
  int WindowHeight = 800;

  InitOpenGL();
  GLFWwindow *Window = CreateWindow(WindowWidth, WindowHeight, "Plus Ultra");

  std::vector<Vertex> Vertices = {
      Vertex(Vector4(0, 0.5, 0, 1), Vector4(1, 0, 1, 1), Vector2(0.5, 1)),
      Vertex(Vector4(0.5, -0.5, 0, 1), Vector4(1, 1, 0, 1), Vector2(1, 0)),
      Vertex(Vector4(-0.5, -0.5, 0, 1), Vector4(0, 1, 1, 1), Vector2(0, 0)),
  };

  std::vector<unsigned int> Indices = {0, 1, 2};

  Shader shader = Shader("src/Shaders/shader.frag", "src/Shaders/shader.vert");
  Material material = Material(shader);
  Geometry geometry = Geometry(Vertices, Indices);

  while (!glfwWindowShouldClose(Window)) {
    glClearColor(0.1, 0.15, 0.2, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    material.Use();

    trans = trans.RotateZ(0.1);
    material.Shader.SetMat4("uTransform", trans);
    geometry.Draw();

    glfwSwapBuffers(Window);

    ProcessInput(Window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}