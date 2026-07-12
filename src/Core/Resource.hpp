#pragma once
#include <string>

struct Resource {
   std::string Name;

   Resource(const std::string &name) : Name(name) {};

   Resource(const Resource &) = delete;

   Resource &operator=(const Resource &) = delete;

   Resource(Resource &&) = default;

   Resource &operator=(Resource &&) = default;

   virtual ~Resource() = default;
};
