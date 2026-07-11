#pragma once

#include "../Uniform.hpp"
#include <memory>
#include <string>
#include <unordered_map>
#include "Core/Resource.hpp"

template<typename T>concept UniformType = std::derived_from<T, Uniform>;

struct Shader : Resource {
   std::string Name;
   unsigned int Id;

   Shader(const std::string &name, const std::string &fragFilepath,
      const std::string &vertFilepath);

   void Use();

   template<UniformType T> void SetUniform(const T &uniform) {
      PendingUniforms[GetUniformLocation(uniform.Name)] = std::make_unique<T>(uniform);
   }

   int GetUniformLocation(const std::string &name);

private:
   std::unordered_map<std::string, unsigned int> UniformLocations;
   std::unordered_map<int, std::unique_ptr<Uniform> > PendingUniforms;

   unsigned int CreateShaderProgram(unsigned int fragShader, unsigned int vertShader);

   unsigned int CreateVertShader(const char *vertSource);

   unsigned int CreateFragShader(const char *fragSource);

   bool CheckUniformExistence(const std::string &name, int location);

   void UploadUniforms();
};
