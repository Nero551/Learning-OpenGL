#pragma once
#include "Utilities/Math/Math.hpp"
#include <string>
#include <unordered_map>
#include <vector>
#include "Core/Core.hpp"

struct Object;

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

class Mesh {
public:
  unsigned int Id;
  std::vector<Vertex> Vertices;
  std::vector<unsigned int> Indices;

  Mesh(const std::vector<Vertex> &vertices, const std::vector<unsigned int> &indices);
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
  Shader Shader;
  Texture Texture0;

  Material(class Shader shader, Texture texture);

  void Use();
};


struct Renderer : Module {
  std::vector<Object> Objects;

  void Start() override;
  void Update(double dt) override;
  void Stop() override;
  void Render() override;
};