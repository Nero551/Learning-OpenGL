#pragma once
#include "../Math/Math.h"

struct Vertex {
  Vector3 Position;
  Vector4 Color;
  Vertex(Vector3 pos, Vector4 col);
};

class Shader {
public:
  unsigned int Id;

  Shader(const std::string &fragFilepath, const std::string &vertFilepath);

public:
  void Use();

public:
  void SetFloat(const std::string &name, float value);

  unsigned int CreateShaderProgram(unsigned int &fragShader, unsigned int &vertShader);
  unsigned int CreateVertShader(const char *vertSource);
  unsigned int CreateFragShader(const char *fragSource);
};