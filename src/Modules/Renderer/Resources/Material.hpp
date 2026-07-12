#pragma once

#include "Shader.hpp"
#include "Texture.hpp"
#include "Core/Resource.hpp"
#include "Utilities/Math/Vector/Vector3.hpp"
#include "Utilities/Math/Vector/Vector4.hpp"


struct Material : Resource {
   static constexpr int MaxTextures = 16;

   Vector4 MaterialColor = Vector4(1, 1, 1, 1);
   Vector3 Ambient = {0.1, 0.1, 0.1};
   Vector3 Diffuse = {1, 1, 1};
   Vector3 Specular = {0.2, 0.2, 0.2};
   float Shininess = 32;

   Material(const std::string &name);

   void AssignTexture(Texture &texture);

   void AssignShader(struct Shader &shader);

   struct Shader &GetShader();

   void Use();

protected:
   std::array<Texture *, MaxTextures> Textures{};
   Shader *Shader = nullptr;
};
