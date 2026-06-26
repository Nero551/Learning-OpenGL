#include "OpenGL.h"
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

void CreateShader(unsigned int &shaderProgram, std::string &vertexCode, std::string &fragCode) {
  const char* vertexSource = vertexCode.c_str();
  const char* fragSource = fragCode.c_str();

  //* Vertex Shader
  unsigned int vertexShader;
  vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexSource, NULL);
  glCompileShader(vertexShader);

  int success;
  char infoLog[512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success){
    glGetShaderInfoLog(vertexShader,512,NULL,infoLog);
    std::cout << "ERROR VERTEX SHADER: " << infoLog << "\n";
  }

  //* Fragment Shader
  unsigned int fragShader;
  fragShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragShader, 1, &fragSource, NULL);
  glCompileShader(fragShader);

  glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
  if (!success){
    glGetShaderInfoLog(fragShader,512,NULL,infoLog);
    std::cout << "ERROR FRAGMENT SHADER: " << infoLog << "\n";
  }


  //* Shader Program
  shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragShader);
  glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success){
    glGetProgramInfoLog(shaderProgram,512,NULL,infoLog);
    std::cout << "ERROR SHADER PROGRAM LINKING: " << infoLog << "\n";
  }

  //* Cleanup
  glDeleteShader(vertexShader);
  glDeleteShader(fragShader);
}

void CreateVAO(unsigned int &VAO, std::vector<Vertex> &vertices,std::vector<unsigned int> &indices) {
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

  //Position
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex) , (void *)offsetof(Vertex, Position));
  glEnableVertexAttribArray(0);

  //Color
  glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex) , (void *) offsetof(Vertex, Color));
  glEnableVertexAttribArray(1);
}

void Draw(unsigned int &ShaderProgram, unsigned int &VAO, int indicesCount) {
  glUseProgram(ShaderProgram);
  glBindVertexArray(VAO);
  glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, 0);
}

float DegToRad(float deg){
  return deg * std::numbers::pi / 180;
}

std::string ReadFile(const std::string& path){
    std::ifstream file(path);

    std::stringstream buffer;
    buffer << file.rdbuf();

    return buffer.str();
}

int main() {
  int WindowWidth = 800;
  int WindowHeight = 800;

  InitOpenGL();
  GLFWwindow *Window = CreateWindow(WindowWidth, WindowHeight, "Plus Ultra");

  std::vector<Vertex> Vertices = {
    Vertex(Vector3(0.5,-0.5,0), Vector4(1,0,1,1)),
    Vertex(Vector3(-0.5,-0.5,0), Vector4(0,1,1,1)),
    Vertex(Vector3(0,0.5,0), Vector4(1,1,0,1)),
  };
  std::vector<unsigned int> Indices = {
    0,1,2,
  };

  std::string vertexShaderSource = ReadFile("src/Shaders/shader.vert");
  std::string fragShaderSource = ReadFile("src/Shaders/shader.frag");

  unsigned int VAO;
  unsigned int ShaderProgram;
  CreateShader(ShaderProgram, vertexShaderSource, fragShaderSource);
  CreateVAO(VAO, Vertices, Indices);

    int timeLocation = glGetUniformLocation(ShaderProgram, "Time");

  while (!glfwWindowShouldClose(Window)) {
    glClearColor(0.1, 0.15, 0.2, 1);
    glClear(GL_COLOR_BUFFER_BIT);


    glUniform1f(timeLocation,glfwGetTime());
    Draw(ShaderProgram, VAO, Indices.size());

    
    glfwSwapBuffers(Window);
    
    ProcessInput(Window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}