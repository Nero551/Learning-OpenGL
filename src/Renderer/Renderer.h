#pragma once
#include <string>
#include <vector>
#include "../Math/Vector.h"

struct Vertex {
  Vector3 Position;
  Vector4 Color;
  Vertex(Vector3 pos, Vector4 col);
};

class Shader {

public:
  unsigned int Id;

  Shader(const std::string &fragFilepath, const std::string &vertFilepath);
  void Use();
  void SetFloat(const std::string &name, float value);
  void SetInt(const std::string &name, int value);
  void SetBool(const std::string &name, bool value);

private:
  unsigned int CreateShaderProgram(unsigned int &fragShader, unsigned int &vertShader);
  unsigned int CreateVertShader(const char *vertSource);
  unsigned int CreateFragShader(const char *fragSource);
};

class Geometry {
public:
  unsigned int Id;
  std::vector<Vertex> Vertices;
  std::vector<unsigned int> Indices;

  Geometry(const std::vector<Vertex> &vertices, const std::vector<unsigned int> &indices);
  void Draw();

private:
  unsigned int CreateVAO();
  unsigned int CreateVBO();
  unsigned int CreateEBO();
  void SetupVertAttrPointers();
};