#pragma once

#include "Shader.hpp"
#include "Texture.hpp"
#include "Core/Resource.hpp"

#include <vector>

struct Material : Resource {
  std::string Name;
  Shader *Shader = nullptr;
  std::vector<Texture *> Textures;

  Material(const std::string &name);

  void AssignTexture(Texture &texture);
  void AssignShader(struct Shader &shader);

  void Use();
};