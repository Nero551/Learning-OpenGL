#pragma once

#include "Shader.hpp"
#include "Texture.hpp"
#include <vector>

struct Material {
  Shader Shader;
  std::vector<Texture> Textures;

  Material(const class Shader &shader);

  void AssignTexture(const Texture &texture);

  void Use();
};