#pragma once
#include "../Uniform.hpp"
#include "Core/Engine.hpp"

struct Vector3Uniform : Uniform {
   Vector3 Value;

   Vector3Uniform(const std::string &name, Vector3 &value) : Uniform(name), Value(value) {}

   void Upload(Shader &shader) override {
      glUniform3f(shader.GetUniformLocation(Name), Value.x, Value.y, Value.z);
   }
};
