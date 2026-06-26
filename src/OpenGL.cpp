#include "OpenGL.h"
#include <iostream>
#include <vector>
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
      Vertex(Vector3(0.5, -0.5, 0), Vector4(1, 0, 1, 1)),
      Vertex(Vector3(-0.5, -0.5, 0), Vector4(0, 1, 1, 1)),
      Vertex(Vector3(0, 0.5, 0), Vector4(1, 1, 0, 1)),
  };
  std::vector<unsigned int> Indices = {
      0,
      1,
      2,
  };

  unsigned int VAO;
  Geometry geometry = Geometry(Vertices, Indices);
  Shader shader = Shader("src/Shaders/shader.frag", "src/Shaders/shader.vert");

  while (!glfwWindowShouldClose(Window)) {
    glClearColor(0.1, 0.15, 0.2, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    shader.SetFloat("uTime", glfwGetTime());
    shader.Use();
    geometry.Draw();

    glfwSwapBuffers(Window);

    ProcessInput(Window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}