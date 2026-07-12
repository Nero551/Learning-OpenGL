#pragma once

#include "Shader.hpp"
#include "Texture.hpp"
#include "Core/Resource.hpp"


struct Material : Resource {
   static constexpr int MaxTextures = 16;
   Shader *Shader = nullptr;

   float AmbientStrength = 0.1;
   float DiffuseStrength = 1;

   Material(const std::string &name);

   void AssignTexture(Texture &texture);

   void AssignShader(struct Shader &shader);

   void Use();

protected:
   std::array<Texture *, MaxTextures> Textures{};
};
