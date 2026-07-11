#pragma once
#include "../Uniform.hpp"
#include "Utilities/Math/Vector/Vector4.hpp"

struct Vector4Uniform : Uniform {
   Vector4 Value;

   Vector4Uniform(const std::string &name, const Vector4 &value) : Uniform(name), Value(value) {}

   void Upload(Shader &shader) override {
      glUniform4f(shader.GetUniformLocation(Name), Value.x, Value.y, Value.z, Value.w);
   }
};
