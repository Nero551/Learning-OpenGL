#pragma once

#include "Shader.hpp"
#include "Texture.hpp"
#include "Core/Resource.hpp"

#include <vector>

struct Material : Resource {
   std::string Name;
   Shader *Shader = nullptr;
   std::array<Texture *, 16> Textures{};

   Material(const std::string &name);

   void AssignTexture(Texture &texture);

   void AssignShader(struct Shader &shader);

   void Use();
};
