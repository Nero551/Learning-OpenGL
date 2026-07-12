#include "Material.hpp"

#include "../Uniforms/FloatUniform.hpp"
#include "../Uniforms/IntUniform.hpp"
#include "../Uniforms/Vector4Uniform.hpp"
#include "Utilities/Services/LoggerService.hpp"

Material::Material(const std::string &name) : Resource(name) {}

void Material::Use() {
   Shader->Use();

   Shader->SetUniform(FloatUniform("AmbientStrength", AmbientStrength));
   Shader->SetUniform(FloatUniform("DiffuseStrength", DiffuseStrength));
   Shader->SetUniform(FloatUniform("SpecularStrength", SpecularStrength));
   Shader->SetUniform(FloatUniform("SpecularShininess", SpecularShininess));
   Shader->SetUniform(Vector4Uniform("MaterialColor", MaterialColor));

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
