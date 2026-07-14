#pragma once
#include "../Enums/Uniform.hpp"
#include "OpenGL.hpp"


struct IntUniform : Uniform {
   int Value;

   IntUniform(const std::string &name, int value) : Uniform(name), Value(value) {}

   void Upload(int location) override {
      glUniform1i(location, Value);
   }
};
