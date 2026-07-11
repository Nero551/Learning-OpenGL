#pragma once
#include "../Uniform.hpp"
#include "Core/Engine.hpp"

struct FloatUniform : Uniform {
   float Value;

   FloatUniform(const std::string &name, float value) : Uniform(name), Value(value) {}

   void Upload(Shader &shader) override {
      glUniform1f(shader.GetUniformLocation(Name), Value);
   }
};
