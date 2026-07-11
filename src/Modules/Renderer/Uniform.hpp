#pragma once
#include <string>

struct Shader;

struct Uniform {
   std::string Name;

   Uniform(const std::string &name) : Name(name) {}
   virtual ~Uniform() {}
   virtual void Upload(Shader &shader) {}
};
