#include "OpenGL.h"
#include <iostream>
#include <vector>
#include "Math/Vector.h"
#include "Renderer/Renderer.h"

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
  glfwSetFramebufferSizeCallback(window, [](GLFWwindow *window, int width, int height) { glViewport(0, 0, width, height); });

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
  int WindowWidth = 800;
  int WindowHeight = 800;

  InitOpenGL();
  GLFWwindow *Window = CreateWindow(WindowWidth, WindowHeight, "Plus Ultra");

  std::vector<Vertex> Vertices = {
      Vertex(Vector3(0.5, 0.5, 0), Vector4(1, 0, 1, 1), Vector2(1, 1)),
      Vertex(Vector3(0.5, -0.5, 0), Vector4(1, 1, 0, 1), Vector2(1, 0)),
      Vertex(Vector3(-0.5, -0.5, 0), Vector4(0, 1, 1, 1), Vector2(0, 0)),
      Vertex(Vector3(-0.5, 0.5, 0), Vector4(1, 1, 0, 1), Vector2(0, 1)),
  };
  std::vector<unsigned int> Indices = {0, 1, 2, 0, 2, 3};

  Texture texture = Texture(0, "src/Images/HexagonsOutline_Niki.png");
  Texture texture2 = Texture(1, "src/Images/ruby.png");
  Texture texture3 = Texture(2, "src/Images/skull.png");
  Shader shader = Shader("src/Shaders/shader.frag", "src/Shaders/shader.vert");
  Material material = Material(shader);
  material.Texture0 = &texture;
  material.Texture1 = &texture2;
  material.Texture2 = &texture3;
  Geometry geometry = Geometry(Vertices, Indices);

  Vector3 vec3 = Vector3(1, 2, 3);
  Vector3 vvec3 = Vector3(1, 2, 3);
  while (!glfwWindowShouldClose(Window)) {
    glClearColor(0.1, 0.15, 0.2, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    material.Use();
    geometry.Draw();

    glfwSwapBuffers(Window);

    ProcessInput(Window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}