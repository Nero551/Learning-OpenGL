#pragma once
#include "Object.hpp"
#include <unordered_map>

struct World {
  // TODO- this guy should own runtime world state (stuff that exist).
  std::unordered_map<unsigned int, Object> Entities;
};
