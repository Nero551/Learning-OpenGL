#pragma once
#include "../Uniform.hpp"
#include "../Resources/Shader.hpp"
#include "OpenGL.hpp"


struct IntUniform : Uniform {
   int Value;

   IntUniform(const std::string &name, int value) : Uniform(name), Value(value) {}

   void Upload(Shader &shader) override {
      glUniform1f(shader.GetUniformLocation(Name), Value);
   }
};
