#include "Material.hpp"

#include "../Uniforms/IntUniform.hpp"
#include "Utilities/Services/LoggerService.hpp"

Material::Material(const std::string &name) : Resource(name) {}

void Material::Use() {
   Shader->Use();

   for (Texture *texture: Textures) {
      if (texture) {
         Shader->SetUniform(IntUniform(texture->Name, texture->Unit));
         texture->Bind();
      }
   }
}

void Material::AssignShader(struct Shader &shader) { Shader = &shader; }

void Material::AssignTexture(Texture &texture) {
   if (texture.Unit >= Textures.size()) {
      LoggerService::Error("Texture out of bounds: " + texture.Name);
   }

   Textures[texture.Unit] = &texture;
}
