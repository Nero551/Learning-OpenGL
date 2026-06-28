#include "Renderer.h"
#include "../FileSystem/FileSystem.h"
#include "../OpenGL.h"
#include <iostream>
#include <string>

Shader::Shader(const std::string &fragFilepath, const std::string &vertFilepath) {
  std::string fragCode = FileSystem::ReadFile(fragFilepath);
  std::string vertCode = FileSystem::ReadFile(vertFilepath);
  const char *fragSource = fragCode.c_str();
  const char *vertSource = vertCode.c_str();

  unsigned int fragShader = CreateFragShader(fragSource);
  unsigned int vertShader = CreateVertShader(vertSource);

  Id = CreateShaderProgram(fragShader, vertShader);

  //* Cleanup
  glDeleteShader(vertShader);
  glDeleteShader(fragShader);
}

void Shader::Use() {
  glUseProgram(Id);
  SetBasicUniforms();
}

void Shader::SetFloat(const std::string &name, float value) {
  int location = GetUniformLocation(name);
  glUniform1f(location, value);
}
void Shader::SetInt(const std::string &name, int value) {
  int location = GetUniformLocation(name);
  glUniform1i(location, value);
}
void Shader::SetBool(const std::string &name, bool value) {
  int location = GetUniformLocation(name);
  glUniform1i(location, value);
}

void Shader::SetMat4(const std::string &name, Matrix4 &mat4) {
  int location = GetUniformLocation(name);
  glUniformMatrix4fv(location, 1, GL_FALSE, *mat4.m);
}

int Shader::GetUniformLocation(const std::string &name) {
  int location;

  if (UniformLocations.contains(name)) {
    location = UniformLocations[name];

  } else {

    location = glGetUniformLocation(Id, name.c_str());
    CheckUniformExistence(name, location);
    UniformLocations[name] = location;
  }
  return location;
}

void Shader::CheckUniformExistence(const std::string &name, int location) {
  if (location == -1) {
    std::cout << "Uniform not found: " << name << '\n';
  }
}

void Shader::SetBasicUniforms() { SetFloat("uTime", glfwGetTime()); }

unsigned int Shader::CreateShaderProgram(unsigned int &fragShader, unsigned int &vertShader) {
  unsigned int id = glCreateProgram();
  glAttachShader(id, vertShader);
  glAttachShader(id, fragShader);
  glLinkProgram(id);

  int success;
  char infoLog[512];
  glGetProgramiv(id, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(id, 512, NULL, infoLog);
    std::cout << "ERROR SHADER PROGRAM LINKING: " << infoLog << "\n";
  }

  return id;
}

unsigned int Shader::CreateFragShader(const char *fragSource) {
  unsigned int fragShader;
  fragShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragShader, 1, &fragSource, NULL);
  glCompileShader(fragShader);

  int success;
  char infoLog[512];
  glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragShader, 512, NULL, infoLog);
    std::cout << "ERROR FRAGMENT SHADER: " << infoLog << "\n";
  }

  return fragShader;
}

unsigned int Shader::CreateVertShader(const char *vertSource) {
  unsigned int vertShader;
  vertShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertShader, 1, &vertSource, NULL);
  glCompileShader(vertShader);

  int success;
  char infoLog[512];
  glGetShaderiv(vertShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertShader, 512, NULL, infoLog);
    std::cout << "ERROR VERTEX SHADER: " << infoLog << "\n";
  }

  return vertShader;
}