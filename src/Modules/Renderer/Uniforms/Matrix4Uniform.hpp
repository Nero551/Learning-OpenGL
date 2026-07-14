#pragma once
#include "../Enums/Uniform.hpp"
#include "OpenGL.hpp"
#include "Utilities/Math/Matrix/Matrix4.hpp"

struct Matrix4Uniform : Uniform {
   Matrix4 Value;

   Matrix4Uniform(const std::string &name, const Matrix4 &value) : Uniform(name), Value(value) {}

   void Upload(int location) override {
      glUniformMatrix4fv(location, 1, GL_TRUE, *Value.m);
   }
};
