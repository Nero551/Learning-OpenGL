#pragma once

#include "Shader.hpp"
#include "Texture.hpp"
#include "Core/Resource.hpp"


struct Material : Resource {
   static constexpr int MaxTextures = 16;
   std::string Name;
   Shader *Shader = nullptr;
   std::array<Texture *, MaxTextures> Textures{};

   Material(const std::string &name);

   void AssignTexture(Texture &texture);

   void AssignShader(struct Shader &shader);

   void Use();
};
