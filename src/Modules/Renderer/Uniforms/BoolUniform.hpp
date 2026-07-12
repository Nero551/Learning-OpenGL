#pragma once
#include "../Uniform.hpp"
#include "OpenGL.hpp"


struct BoolUniform : Uniform {
   bool Value;

   BoolUniform(const std::string &name, bool value) : Uniform(name), Value(value) {}

   void Upload(int location) override {
      glUniform1i(location, Value);
   }
};
