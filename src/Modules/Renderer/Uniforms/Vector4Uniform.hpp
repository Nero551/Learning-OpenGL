#pragma once
#include "../Uniform.hpp"
#include "Utilities/Math/Vector/Vector4.hpp"

struct Vector4Uniform : Uniform
{
   Vector4 Value;

   Vector4Uniform(const std::string& name, const Vector4& value) : Uniform(name), Value(value) {}

   void Upload(int location) override
   {
      glUniform4fv(location, 1, &Value.x);
   }
};
