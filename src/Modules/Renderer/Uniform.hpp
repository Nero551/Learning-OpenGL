#pragma once
#include <string>


struct Uniform {
   std::string Name;

   Uniform(const std::string &name) : Name(name) {};
   virtual ~Uniform() {}

   virtual void Upload(int location) = 0;
};
