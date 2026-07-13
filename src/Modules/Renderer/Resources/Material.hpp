#pragma once

#include "Shader.hpp"
#include "Texture.hpp"
#include "Core/Resource.hpp"
#include "Utilities/Math/Vector/Vector3.hpp"
#include "Utilities/Math/Vector/Vector4.hpp"
#include "Utilities/SafePtr.hpp"


struct Material : Resource {
   static constexpr int MaxTextures = 16;
   SafePtr<Shader> Shader{"Material Has No Shader Assigned"};

   Vector4 Color = {1};
   Vector3 Ambient = {1};
   Vector3 Diffuse = {1};
   Vector3 Specular = {1};
   float Shininess = 32;

   Material(const std::string &name);

   void AssignTexture(Texture &texture);

   void Use();

protected:
   std::array<Texture *, MaxTextures> Textures{};

   void SetProperties();
};
