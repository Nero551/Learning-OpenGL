#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include "../Math/Math.h"

struct Vertex {
  Vector4 Position;
  Vector4 Color;
  Vector2 UV;

  Vertex(Vector4 pos, Vector4 col, Vector2 uv);
};

class Shader {

public:
  unsigned int Id;

  Shader(const std::string &fragFilepath, const std::string &vertFilepath);
  void Use();
  void SetFloat(const std::string &name, float value);
  void SetInt(const std::string &name, int value);
  void SetBool(const std::string &name, bool value);
  void SetMat4(const std::string &name, Matrix4 &mat4);

private:
  std::unordered_map<std::string, unsigned int> UniformLocations;

  void SetBasicUniforms();
  unsigned int CreateShaderProgram(unsigned int fragShader, unsigned int vertShader);
  unsigned int CreateVertShader(const char *vertSource);
  unsigned int CreateFragShader(const char *fragSource);
  void CheckUniformExistence(const std::string &name, int location);
  int GetUniformLocation(const std::string &name);
};

class Geometry {
public:
  unsigned int Id;
  std::vector<Vertex> Vertices;
  std::vector<unsigned int> Indices;

  Geometry(const std::vector<Vertex> &vertices, const std::vector<unsigned int> &indices);
  void Draw();

private:
  unsigned int VBO;
  unsigned int EBO;

  unsigned int CreateVAO();
  unsigned int CreateVBO();
  unsigned int CreateEBO();
  void SetupVertAttrPointers();
};

class Texture {
public:
  unsigned int Id;
  unsigned int Unit;
  Texture(unsigned int unit, const std::string &imagePath);

  void Bind();

private:
  void SetParameters();
};

struct Material {

public:
  Shader &Shader;
  Texture *Texture0 = nullptr;
  Texture *Texture1 = nullptr;
  Texture *Texture2 = nullptr;

  Material(class Shader &shader);

  void Use();
};