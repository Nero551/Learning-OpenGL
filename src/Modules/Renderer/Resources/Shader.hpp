#pragma once

#include "Core/Resource.hpp"

#include <string>
#include <unordered_map>
#include "Utilities/Math/Matrix/Matrix4.hpp"

struct Shader : Resource {
  std::string Name;
  unsigned int Id;

  Shader(const std::string &name, const std::string &fragFilepath, const std::string &vertFilepath);
  void Use();
  void SetFloat(const std::string &name, float value);
  void SetInt(const std::string &name, int value);
  void SetBool(const std::string &name, bool value);
  void SetMat4(const std::string &name, const Matrix4 &mat4);

private:
  std::unordered_map<std::string, unsigned int> UniformLocations;

  void SetBasicUniforms();
  unsigned int CreateShaderProgram(unsigned int fragShader, unsigned int vertShader);
  unsigned int CreateVertShader(const char *vertSource);
  unsigned int CreateFragShader(const char *fragSource);
  void CheckUniformExistence(const std::string &name, int location);
  int GetUniformLocation(const std::string &name);
};