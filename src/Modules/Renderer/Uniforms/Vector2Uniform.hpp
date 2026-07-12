#pragma once
#include "../Uniform.hpp"
#include "Core/Engine.hpp"

struct Vector2Uniform : Uniform {
   Vector2 Value;

   Vector2Uniform(const std::string &name, const Vector2 &value) : Uniform(name), Value(value) {}

   void Upload(int location) override {
      glUniform2fv(location, 1, &Value.x);
   }
};
