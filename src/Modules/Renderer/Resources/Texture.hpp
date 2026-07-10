#pragma once

#include <string>
#include "Core/Resource.hpp"

struct Texture : Resource {
  std::string Name;
  unsigned int Id;
  unsigned int Unit;
  Texture(const std::string &name, unsigned int unit, const std::string &imagePath);

  void Bind();

private:
  void SetParameters();
};