#include "OpenGL.h"
#include <GLFW/glfw3.h>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <vector>
#include "Math/Vector.h"
#include "Renderer/Renderer.h"
#include <fstream>
#include <sstream>
#include <string>

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

void CreateVAO(unsigned int &VAO, std::vector<Vertex> &vertices, std::vector<unsigned int> &indices) {
  //* Vertex Array Object (VAO)
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  //* Vertex Buffer Object (VBO)
  unsigned int VBO;
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

  unsigned int EBO;
  glGenBuffers(1, &EBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(float), indices.data(), GL_STATIC_DRAW);

  // Position
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, Position));
  glEnableVertexAttribArray(0);

  // Color
  glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, Color));
  glEnableVertexAttribArray(1);
}

void Draw(Shader &shader, unsigned int &VAO, int indicesCount) {
  shader.Use();
  glBindVertexArray(VAO);
  glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, 0);
}

float DegToRad(float deg) { return deg * std::numbers::pi / 180; }

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
  Shader shader = Shader("src/Shaders/shader.frag", "src/Shaders/shader.vert");
  CreateVAO(VAO, Vertices, Indices);


  while (!glfwWindowShouldClose(Window)) {
    glClearColor(0.1, 0.15, 0.2, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    shader.SetFloat("Time", glfwGetTime());
    Draw(shader, VAO, Indices.size());

    glfwSwapBuffers(Window);

    ProcessInput(Window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}